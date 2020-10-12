#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/contiguous-array/
// Interesting: O(n) solution with hash map and an accumulator with 0 computed as -1 (nice)

// Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

// Example 1:
// Input: [0,1]
// Output: 2
// Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.

// Example 2:
// Input: [0,1,0]
// Output: 2
// Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.

// Note: The length of the given binary array will not exceed 50,000.

int findMaxLength(vector<int> &nums) {
	int acc = 0;
	int maxLength = 0;
	unordered_map<int, int> seen;
	seen[0] = -1;

	for(int i = 0; i < nums.size(); ++i) {
		acc += (nums[i] == 0 ? -1 : 1);
		if(seen.find(acc) != seen.end()) {
			maxLength = max(maxLength, i - seen[acc]);
		} else {
			seen[acc] = i;
		}
	}
	
	return maxLength;
}

int main() {
	vector<int> nums = {0, 1, 0, 1, 0}; // ans: 4
	cout << "Answer: " << findMaxLength(nums) << endl;

	return 0;
}







