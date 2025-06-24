#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/longest-consecutive-sequence

// Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
// You must write an algorithm that runs in O(n) time.

// Example 1:
// Input: nums = [100,4,200,1,3,2]
// Output: 4
// Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

// Example 2:
// Input: nums = [0,3,7,2,5,8,4,6,0,1]
// Output: 9

// Example 3:
// Input: nums = [1,0,1,2]
// Output: 3

// Constraints:
// 0 <= nums.length <= 10^5
// -10^9 <= nums[i] <= 10^9


// Idea: Go only through the hash set of numbers and traverse each path only once - starting traversing only if that 
// number could be the end of a path (that is if num + 1 is not in the set).
// Could think: if that number could be the start of a path too (num - 1 not in the set) - symmetric.
// In spite of the 2 for's below it visits each distinct number only 2 times - so O(N) in time, and also space.
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> nums_set(nums.begin(), nums.end());
    int longest_size = 0;

    for (int num : nums_set) {
        if (!nums_set.count(num + 1)) {
			int curr_size = 1;
            for (; nums_set.count(num - 1); --num) {
                ++curr_size;
            }
            longest_size = max(longest_size, curr_size);
        }
    }

    return longest_size;

	// Below is a solution if there was the requirement of the numbers to be in order in the original nums.
	// Lesson: pay attention to your constraints and the examples given!
    /*
    for (int num : nums) {
        longest_size_ending_here[num] = 1;
        if (longest_size_ending_here.count(num - 1)) {
            longest_size_ending_here[num] += longest_size_ending_here[num - 1];
        }
        longest_size_found = max(longest_size_found, longest_size_ending_here[num]);
    }
	*/
}

int main() {
    // vector<int> nums = {2, 20, 4, 10, 3, 4, 5};  // ans: 4
    vector<int> nums = {0, 3, 2, 5, 4, 6, 1, 1};  // ans: 7
    cout << "Answer: " << longestConsecutive(nums) << endl;

    return 0;
}