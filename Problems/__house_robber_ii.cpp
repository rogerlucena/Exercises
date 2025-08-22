#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/house-robber-ii
// https://leetcode.com/problems/house-robber-ii
// Remember: 1-dimensional DP, but the values for memo with flag == 1 will be different than memo with flag == 0,
// thus will need two 1-dimensional memo as done below (elegant).
// Could do the normal "House Robber" for nums_aux(nums.begin(), nums.end() - 1) and 
// nums_aux(nums.begin() + 1, nums.end()) too, but I felt it less elegant as below.
// Normal "House Robber" (solution also below): https://neetcode.io/problems/house-robber / https://leetcode.com/problems/house-robber

// You are given an integer array nums where nums[i] represents the amount of money the ith house has. The houses 
// are arranged in a circle, i.e. the first house and the last house are neighbors.
// You are planning to rob money from the houses, but you cannot rob two adjacent houses because the security system
// will automatically alert the police if two adjacent houses were both broken into.
// Return the maximum amount of money you can rob without alerting the police.

// Example 1:
// Input: nums = [3,4,3]
// Output: 4

int dfs(int i, int flag, vector<int>& nums, vector<vector<int>>& memo) {
    if (i >= nums.size() || (flag == 1 && i == nums.size() - 1)) return 0;
    if (memo[flag][i] != -1) return memo[flag][i];
    memo[flag][i] = max(dfs(i + 1, flag, nums, memo),
                        nums[i] + dfs(i + 2, flag, nums, memo));
    return memo[flag][i];
}

int rob(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];

    vector<vector<int>> memo(2, vector<int>(nums.size(), -1));
    return max(dfs(0, 1, nums, memo), dfs(1, 0, nums, memo));
}


// Normal "House Robber": (standard 1-dimensional DP)
// https://neetcode.io/problems/house-robber 
// https://leetcode.com/problems/house-robber
// You are given an integer array nums where nums[i] represents the amount of money the ith house has. The houses are 
// arranged in a straight line, i.e. the ith house is the neighbor of the (i-1)th and (i+1)th house.
// You are planning to rob money from the houses, but you cannot rob two adjacent houses because the security system
// will automatically alert the police if two adjacent houses were both broken into.
// Return the maximum amount of money you can rob without alerting the police.

// Example 1:
// Input: nums = [1,1,3,3]
// Output: 4

// Top Down (Xandão acha bonito assim recursivo):
int robRecursive(vector<int>& nums, int i, vector<int>& memo) {
    if (i >= nums.size()) {
        return 0;
    }
    if (memo[i] != -1) {
        return memo[i];
    }

    memo[i] = max(nums[i] + robRecursive(nums, i + 2, memo),
                  robRecursive(nums, i + 1, memo));
    return memo[i];
}

int rob(vector<int>& nums) {
    vector<int> memo(nums.size(), -1);
    return robRecursive(nums, 0, memo);
}

// Bottom-up iterative:
int rob(vector<int>& nums) {
    int n = nums.size();
    vector<int> memo(n + 1, -1);
    memo[n] = 0;
    memo[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        memo[i] = max(nums[i] + memo[i + 2], memo[i + 1]);
    }
    
    return memo[0];
}

int main() {
	cout << "Hello, World!";
	return 0;
}