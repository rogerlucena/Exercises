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

// Another way I did without recursion comparing mid with right to determine the case (mid and left together in the same
// sorted segment, or mid and right together - they 3 in the same sorted segment also correctly dealt below).
// Visit __find_minimum_in_rotated_sorted_array.cpp for more info on the way to think.
int search(vector<int>& nums, int target) {
	int l = 0;
	int r = nums.size() - 1;

    while (l <= r) {
		int m = l + (r - l) / 2;
		if (nums[m] == target) {
			return m;
		}

		if (nums[m] < nums[r]) {
			if (nums[m] > target || nums[r] < target) {
				r = m - 1;
			} else {
				l = m + 1;
			}
		} else {
			if (nums[m] < target || nums[l] > target) {
                l = m + 1;
            } else {
                r = m - 1;
            }
		}
    }

    return -1;
}

int main() {
	vector<int> nums = {4,5,6,7,0,1,2};
	int target = 0; // ans: 4

	// vector<int> nums = {3,1};
	// int target = 1; // ans: 1

	cout << "Answer: " << search(nums, target) << endl;

	return 0;
}