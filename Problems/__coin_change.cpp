#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://neetcode.io/problems/coin-change
// https://leetcode.com/problems/coin-change
// Remember: 1D DP here is enough, which coins used are not important, just the amount dimension is 
// enough and simpler and better in space - O(amount) in space, instead of O(amount*n) - do not overcomplicate!

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

int main() {
	cout << "Hello, World!";
	return 0;
}