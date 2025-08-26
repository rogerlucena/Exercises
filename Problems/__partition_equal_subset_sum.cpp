#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/partition-equal-subset-sum
// https://leetcode.com/problems/partition-equal-subset-sum
// Remember: enough to get a subset summing to total_sum/2 -> use that as the target.
// DP with n in one dimention and target in the other, memo[i][t] gives if possible to get a subset 
// 		summing to t taking nums from i onwards - avoids repeated work for same subportion of nums trying to get the same target. 

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

// Top-down (more intuitive ans easier to come up):
// O(n*target) in time and space, where target is total_sum/2.
bool canPartitionRecursive(vector<int>& nums, int i, int target, vector<vector<int>>& memo) {
    if (target == 0) {
        return true;
    }
    if (i == nums.size() || target < 0) {
        return false;
    }
    if (memo[i][target] != -1) {
        return memo[i][target];
    }

    memo[i][target] =
        canPartitionRecursive(nums, i + 1, target, memo) ||
        canPartitionRecursive(nums, i + 1, target - nums[i], memo);
    return memo[i][target];
}

bool canPartition(vector<int>& nums) {
    int total_sum = 0;
    for (int num : nums) {
        total_sum += num;
    }
    if (total_sum % 2 == 1) {
        return false;
    }

    vector<vector<int>> memo(nums.size(), vector<int>(total_sum / 2 + 1, -1));
    return canPartitionRecursive(nums, 0, total_sum / 2, memo);
}

// Botton-up (better leetcode 30% in memory than above, more or less same in time):
// Same complexity in time/space as above.
bool canPartition(vector<int>& nums) {
	int sum = 0;
	for (int num : nums) {
		sum += num;
	}
	if (sum % 2 != 0) {
		return false;
	}

	int target = sum / 2;
	int n = nums.size();
	// dp[i][j] -> considering nums from 0 to i-1, gives if possible to get a subset summing to j.
	vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

	for (int i = 0; i <= n; i++) {
		dp[i][0] = true;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= target; j++) {
			if (nums[i - 1] <= j) {
				dp[i][j] = dp[i - 1][j] ||
							dp[i - 1][j - nums[i - 1]];
			} else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	return dp[n][target];
}

// My older solution below:
// DP, idea: size of "memo" in dimension 1 is the totalSum 
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