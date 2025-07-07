#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/find-minimum-in-rotated-sorted-array
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array
// Quick review: In a rotated sorted array, mid can be in the same sorted segment as left or right, compare to right to find out.
// If they three are in the same sorted segment it is also correctly dealt below.

// Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, 
// the array nums = [0,1,2,4,5,6,7] might become:

// [4,5,6,7,0,1,2] if it was rotated 4 times.
// [0,1,2,4,5,6,7] if it was rotated 7 times.

// Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the 
// array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

// Given the sorted rotated array nums of unique elements, return the minimum element of this array.
// You must write an algorithm that runs in O(log n) time.

// Example 1:
// Input: nums = [3,4,5,1,2]
// Output: 1
// Explanation: The original array was [1,2,3,4,5] rotated 3 times.

// Example 2:
// Input: nums = [4,5,6,7,0,1,2]
// Output: 0
// Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

// Constraints:
// n == nums.length
// 1 <= n <= 5000
// -5000 <= nums[i] <= 5000
// All the integers of nums are unique.
// nums is sorted and rotated between 1 and n times.

// O(log n) in time.
// In a rotated sorted array, mid can be in the same sorted segment as left or right, compare to right to find out.
// If they three are in the same sorted segment it is also correctly dealt below.
int findMin(vector<int> &nums) {
	int l = 0;
	int r = nums.size() - 1;
	int ans = nums[0];

	while (l <= r) {
        int m = l + (r - l) / 2;
		ans = min(ans, nums[m]);

		if (nums[m] < nums[r]) { // curiosity: remember that m will never be equal to r other than the case on which l == r.
			r = m - 1;
		} else {
			l = m + 1;
		}
    }

	return ans;
}

// "Lower bound" solution from Neetcode below:
int findMin(vector<int>& nums) {
	int l = 0, r = nums.size() - 1;
	while (l < r) { // exits only when l == r, we never have r < l here.
		int m = l + (r - l) / 2;
		if (nums[m] < nums[r]) {
			r = m; // m should still be kept in the valid interval.
		} else {
			l = m + 1; // in this case we can discard m.
		}
	}

	return nums[l];
}

int main() {
	cout << "Hello, World!";
	return 0;
}