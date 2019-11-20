#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/partition-equal-subset-sum/submissions/
// DP, idea: size of "memo" in dimension 1 is the totalSum 

// Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

// Note:
// Each of the array element will not exceed 100.
// The array size will not exceed 200.
 
// Example 1:
// Input: [1, 5, 11, 5]
// Output: true
// Explanation: The array can be partitioned as [1, 5, 5] and [11].
 
// Example 2:
// Input: [1, 2, 3, 5]
// Output: false
// Explanation: The array cannot be partitioned into equal sum subsets.

bool canPartitionHelper(vector<int> &nums, int pos, int currSum, int totalSum, vector<vector<int>> &memo) {
	if(memo[pos][currSum] != -1) {
		return memo[pos][currSum];
	}

	if(pos == nums.size() || currSum > totalSum/2) {
		memo[pos][currSum] = 0;
	} else if(currSum + nums[pos] == totalSum/2) {
		memo[pos][currSum] = 1;
	} else {
		memo[pos][currSum] = canPartitionHelper(nums, pos+1, currSum + nums[pos], totalSum, memo) || 
							 canPartitionHelper(nums, pos+1, currSum, totalSum, memo);
	}

	return memo[pos][currSum];
}

bool canPartition(vector<int> &nums) {
	int totalSum = 0;
	for(int el : nums) {
		totalSum += el;
	}

	if(nums.empty() || totalSum % 2 == 1) {
		return false;
	}

	vector<vector<int>> memo(nums.size()+1, vector<int>(totalSum+1, -1));

	return canPartitionHelper(nums, 0, 0, totalSum, memo);
}

int main() {
	vector<int> nums = {1, 5, 11, 5}; // ans: 1
	// vector<int> nums = {1, 2, 3, 5}; // ans: 0
	cout << "Answer: " << canPartition(nums) << endl;

	return 0;
}