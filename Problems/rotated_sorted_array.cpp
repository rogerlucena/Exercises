#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/search-in-rotated-sorted-array/
// another approach: find pivot and select a halve to do a normal binary search

// Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
// (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
// You are given a target value to search. If found in the array return its index, otherwise return -1.
// You may assume no duplicate exists in the array.

// Your algorithm's runtime complexity must be in the order of O(log n).

// Example 1:
// Input: nums = [4,5,6,7,0,1,2], target = 0
// Output: 4

int searchFromTo(const vector<int> &nums, int target, int from, int to) {
	if(from > to) {
		return -1;
	}

	int mid = (from + to) / 2;
	if(nums[mid] == target) {
		return mid;
	}

	if(nums[mid] >= nums[from]) { // the "=" in ">=" is importante here (to catch rounded case)
		return nums[mid] < target || (nums[from] > target) ? 
					searchFromTo(nums, target, mid+1, to) : 
					searchFromTo(nums, target, from, mid-1);
	} else {
		return nums[mid] > target || (target > nums[to]) ? 
					searchFromTo(nums, target, from, mid-1) : 
					searchFromTo(nums, target, mid+1, to);
	}
}

int search(vector<int> &nums, int target) {
	return searchFromTo(nums, target, 0, nums.size()-1);
}

int main() {
	vector<int> nums = {4,5,6,7,0,1,2};
	int target = 0; // ans: 4

	// vector<int> nums = {3,1};
	// int target = 1; // ans: 1

	cout << "Answer: " << search(nums, target) << endl;

	return 0;
}