#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://neetcode.io/problems/target-sum
// https://leetcode.com/problems/target-sum
// Remember: 2D DP on which one dimension is curr_sum (size is 2 * total_sum + 1), could have used 
// a vector<unordered_map<int, int>> too for memo.

// Top-down:
// O(N * M) in time and space, where M is the total_sum.
int findTargetSumWaysRecursive(vector<int>& nums, int i, int curr_sum, int target, int total_sum, vector<vector<int>>& memo) {
    if (i == nums.size()) {
        return curr_sum == target;
    }
    if (memo[i][curr_sum + total_sum] != -1) { // since curr_sum can be negative in the interval [-total_sum, total_sum].
        return memo[i][curr_sum + total_sum];
    }

    memo[i][curr_sum + total_sum] =
        findTargetSumWaysRecursive(nums, i + 1, curr_sum + nums[i], target, total_sum, memo) +
        findTargetSumWaysRecursive(nums, i + 1, curr_sum - nums[i], target, total_sum, memo);

    return memo[i][curr_sum + total_sum];
}

int findTargetSumWays(vector<int>& nums, int target) {
    int total_sum = 0;
    for (int num : nums) {
        total_sum += num;
    }
    vector<vector<int>> memo(nums.size(), vector<int>(2 * total_sum + 1, -1)); // curr_sum in the interval [-total_sum, total_sum].

    return findTargetSumWaysRecursive(nums, 0, 0, target, total_sum, memo);
}

// Bottom-up:
int findTargetSumWays(vector<int>& nums, int target) {
    int n = nums.size();
    vector<unordered_map<int, int>> dp(n + 1); // dp[i][j] -> #ways for the i first nums trying to sum to j.
    dp[0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (auto &p : dp[i]) {
            dp[i + 1][p.first + nums[i]] += p.second;
            dp[i + 1][p.first - nums[i]] += p.second;
        }
    }
    return dp[n][target];
}

int main() {
	cout << "Hello, World!";
	return 0;
}