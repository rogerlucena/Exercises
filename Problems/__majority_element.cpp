#include <iostream>
#include <unordered_map>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://neetcode.io/problems/majority-element/question?list=neetcode250
// http://leetcode.com/problems/majority-element/description

// Given an array nums of size n, return the majority element.
// The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the 
// majority element always exists in the array.

// Example 1:
// Input: nums = [3,2,3]
// Output: 3

// Example 2:
// Input: nums = [2,2,1,1,1,2,2]
// Output: 2

// Constraints:
// n == nums.length
// 1 <= n <= 5 * 10^4
// -10^9 <= nums[i] <= 10^9
// The input is generated such that a majority element will exist in the array.

// To be O(1) in space use the Boyer-Moore Voting Algorithm:
// (Since the majority element appears more than half the time, it will survive this elimination
// process and remain as the final candidate)
int majorityElement(vector<int>& nums) {
	int ans = 0, count = 0;
	for (int num : nums) {
		if (count == 0) {
			ans = num;
		}
		count += (num == ans) ? 1 : -1;
	}

	return ans;
}

// O(n) in time above, if using a hash map to count frequencies would be the same in time but O(n) in space.

// Another nice solution would be to use a vector of size 32 and count bits -> by the end the bits with
// "count > n/2" compound our answer with "ans |= (1 << i)" -> O(n * 32) in time and O(32) in space:
int majorityElementBitManipulation(vector<int>& nums) {
	int n = nums.size();
	vector<int> bit(32, 0);
	for (int num : nums) {
		for (int i = 0; i < 32; ++i) {
			bit[i] += (num >> i) & 1;
		}
	}

	int ans = 0;
	for (int i = 0; i < 32; ++i) {
		if (bit[i] > n / 2) {
			ans |= (1 << i);
		}
	}
	
	return ans;
}

// Generalizing to k-Majority Elements (> n/k): at most k-1 elements in your answer (proof by contradiction).
// https://neetcode.io/problems/majority-element-ii
// https://leetcode.com/problems/majority-element-ii

// Given an integer array of size n, find all elements that appear more than ⌊n/3⌋ times.
// Example 1:
// Input: nums = [3,2,3]
// Output: [3]

// Example 2:
// Input: nums = [1]
// Output: [1]

// Example 3:
// Input: nums = [1,2]
// Output: [1,2]

// Example 4:
// Input: nums = [1,2,3]
// Output: []
 
// Constraints:
// 1 <= nums.length <= 5 * 10^4
// -10^9 <= nums[i] <= 10^9

// This generalizes the Boyer-Moore approach (also known as the Misra-Gries algorithm) and can be
// extended to find elements appearing more than n/k times (just use k-1 counts and candidates).
// Intuition: think about a room with people holding cards with numbers, whenever there is a triplet with 3 different numbers 
// these people leave the room, for the 2 heavy-hitters they mathematically will not be all eliminated: https://gemini.google.com/share/6ee3d26304f1
// O(n) in time and O(1) in space below:
vector<int> majorityElementGeneralized(vector<int>& nums) {
	int size = nums.size();
	unordered_map<int, int> counts;
    vector<int> ans;

    for (int num : nums) {
		if (counts.find(num) != counts.end()) {
			++counts[num];
		} else if (counts.size() < 2) {
			counts[num] = 1;
		} else {
			for (auto it = counts.begin(); it != counts.end();) {
				if (--it->second == 0) {
					it = counts.erase(it);  // updates it to the next valid iterator, if doing just ++it inside "for" above would give iterator error (invalid iterator to increment).
				} else {
					++it;
				}
			}
		}
	}

	unordered_map<int, int> freqs;
	for (const auto& [num, _] : counts) {
		freqs[num] = 0;
	}

	for (int num : nums) {
		if (freqs.find(num) != freqs.end()) {
			++freqs[num];
		}
	}

	for (const auto& [num, freq] : freqs) {
        if (freq > size / 3) {
			ans.push_back(num);
        }
    }

	return ans;
}

int main() {
	vector<int> nums = {1,2,3};
	
	vector<int> ans = majorityElementGeneralized(nums);
	cout << "Answer:" << endl;
	cout << "Size: " << ans.size() << endl;
	printVector(ans);

	return 0;
}