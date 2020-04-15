#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/product-of-array-except-self/

// Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal
// to the product of all the elements of nums except nums[i].

// Example:

// Input:  [1,2,3,4]
// Output: [24,12,8,6]
// Constraint: It's guaranteed that the product of the elements of any prefix or suffix of the array 
// (including the whole array) fits in a 32 bit integer.

// Note: Please solve it without division and in O(n).

// Follow up:
// Could you solve it with constant space complexity? (The output array does not count as extra 
// space for the purpose of space complexity analysis.)

vector<int> productExceptSelf(vector<int> &nums) {
    vector<int> ans(nums.size(), 1);

	for(int i = 1, acc = 1; i < nums.size(); ++i) {
		acc *= nums[i-1];
		ans[i] *= acc;
	}

	for(int i = nums.size()-2, acc = 1; i >= 0; --i) {
		acc *= nums[i+1];
		ans[i] *= acc;
	}

	return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}