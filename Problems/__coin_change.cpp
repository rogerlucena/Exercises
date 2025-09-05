#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://neetcode.io/problems/coin-change
// https://leetcode.com/problems/coin-change
// https://neetcode.io/problems/coin-change-ii (Below)
// https://leetcode.com/problems/coin-change-ii
// Remember: 1D DP here is enough, which coins used are not important, just the amount dimension is 
// enough and simpler and better in space - O(amount) in space, instead of O(amount*n) - do not overcomplicate!
// To get the min number of coins as above the 1D DP is enough because what only matters is the total number of 
// coins used and not which coins were used, but to get the total number of ways to sum amount which coins 
// were used becomes important to differentiate two ways - then the 2D DP becomes necessary to avoid counting
// more than once some possibilities - see Coin Change II below.

// You are given an integer array coins representing coins of different denominations 
// (e.g. 1 dollar, 5 dollars, etc) and an integer amount representing a target amount of money.
// Return the fewest number of coins that you need to make up the exact target amount. If it is impossible 
// to make up the amount, return -1.

// You may assume that you have an unlimited number of each coin.

// Example 1:
// Input: coins = [1,5,10], amount = 12
// Output: 3

// Top-down approach - recursive (website solution):
// O(n*t) in time where t is the amount, O(t) in space.
int coinChangeRecursive(vector<int>& coins, int amount, unordered_map<int, int>& memo) {
    if (amount == 0) {
        return 0;
    }
    if (memo.count(amount)) {
        return memo[amount];
    }

    int res = INT_MAX;
    for (int coin : coins) {
        if (amount - coin >= 0) {
            int result = coinChangeRecursive(coins, amount - coin, memo);
            if (result != INT_MAX) {
                res = min(res, 1 + result);
            }
        }
    }

    memo[amount] = res;
    return res;
}

int coinChange(vector<int>& coins, int amount) {
    unordered_map<int, int> memo;
    int minCoins = coinChangeRecursive(coins, amount, memo);
    return minCoins == INT_MAX ? -1 : minCoins;
}


// Bottom-up approach - iterative (neat, clear and well done - website solution):
// O(n*t) in time, O(t) in space.
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1); // since coins[i] >= 1, the maximum n_coins is amount, so amount+1 corresponds to INT_MAX here.
    dp[0] = 0;
    for (int curr_amount = 1; curr_amount <= amount; ++curr_amount) {
        for (int coin : coins) {
            if (coin <= curr_amount) {
                dp[curr_amount] = min(dp[curr_amount], dp[curr_amount - coin] + 1); // if dp[curr_amount - coin] not possible it will be amount+1, so amount+2 here, and then dp[curr_amount] will not change.
            }
        }
    }
    
    return dp[amount] > amount ? -1 : dp[amount]; // if it is still amount+1 thus not possible, thus -1.
}


// https://neetcode.io/problems/coin-change-ii
// https://leetcode.com/problems/coin-change-ii

// You are given an integer array coins representing coins of different denominations (e.g. 1 dollar, 5 dollars, 
// etc) and an integer amount representing a target amount of money.
// Return the number of distinct combinations that total up to amount. If it's impossible to make up the amount, 
// return 0.
// You may assume that you have an unlimited number of each coin and that each value in coins is unique.

// Example 1:
// Input: amount = 4, coins = [1,2,3]
// Output: 4
// Explanation:
// 1+1+1+1 = 4
// 1+1+2 = 4
// 2+2 = 4
// 1+3 = 4

// Top-down (more intuitive to come up during interview):
int changeRecursive(const vector<int>& coins, int i, int amount, vector<vector<int>>& memo) {
    if (amount == 0) {
        return 1;
    }
    if (i == coins.size()) {
        return 0;
    }
    if (memo[i][amount] != -1) {
        return memo[i][amount];
    }

    memo[i][amount] = 0;
    for (int quant = 0; quant <= amount / coins[i]; ++quant) {
        memo[i][amount] +=
            changeRecursive(coins, i + 1, amount - quant * coins[i], memo);
    }

    return memo[i][amount];
}

int change(int amount, vector<int>& coins) {
    vector<vector<int>> memo(coins.size(), vector<int>(amount + 1, -1));
    return changeRecursive(coins, 0, amount, memo);
}

// Bottom-up (less intuitive to come up fastly):
int change(int amount, vector<int>& coins) {
    int n = coins.size();
    sort(coins.begin(), coins.end());
    // dp[i][j] = using coins from i onwards, gives #ways to get amount j.
    vector<vector<uint>> dp(n + 1, vector<uint>(amount + 1, 0)); 

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int a = 0; a <= amount; a++) {
            if (a >= coins[i]) {
                dp[i][a] = dp[i + 1][a];
                dp[i][a] += dp[i][a - coins[i]]; // not using i+1 here allows using coins[i] multiple times.
            }
        }
    }

    return dp[0][amount];
}

int main() {
	cout << "Hello, World!";
	return 0;
}