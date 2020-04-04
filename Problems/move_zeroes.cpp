#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/move-zeroes/

// Given an array nums, write a function to move all 0's to the end of 
// it while maintaining the relative order of the non-zero elements.

// Example:
// Input: [0,1,0,3,12]
// Output: [1,3,12,0,0]

void moveZeroes(vector<int> &nums) {
	for(int i = 0, j = 0; j < nums.size(); ) {
		if(nums[i] == 0) {
			if(nums[j] != 0) {
				swap(nums[i], nums[j]);
				++i;
			} 

			++j;
		} else {
			++i;
			++j;
		}
	}
}

int main() {
	vector<int> nums = {0, 1, 0, 3, 12};
	moveZeroes(nums);
	cout << "Answer: " << endl;
	printVector(nums);

	return 0;
}