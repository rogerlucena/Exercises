#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/jump-game/
// Think backwards (impt!) and in O(n), you need only the lastPossibleStart! =D

// Given an array of non-negative integers, you are initially positioned at the first index of the array.
// Each element in the array represents your maximum jump length at that position.
// Determine if you are able to reach the last index.

// Example:
// Input: [2,3,1,1,4]
// Output: true
// Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

bool canJump(vector<int> &nums) {
	int len = nums.size();
	int lastPossibleStart = len-1;

	for(int i = len-2; i >= 0; --i) {
		if(lastPossibleStart - i <= nums[i]) {
			lastPossibleStart = i;
		}
	}

	return lastPossibleStart == 0;
}

int main() {
	vector<int> nums = {2,3,1,1,4}; // ans: true
	// vector<int> nums = {3,2,1,0,4}; // ans: false

	cout << "Answer: " << canJump(nums) << endl;
	return 0;
}