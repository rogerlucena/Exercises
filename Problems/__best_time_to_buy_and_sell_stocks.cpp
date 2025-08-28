#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/best-time-to-buy-and-sell-stocks-i/
// Versions II, with cooldown, and III of the problem are below!
// Classic: find max A[j]-A[i], with j > i

// Say you have an array, A, for which the ith element is the price of a given stock on day i.
// If you were only permitted to complete at most one transaction (ie, buy one and sell one share
// of the stock), design an algorithm to find the maximum profit.

// Return the maximum possible profit.

// Constraints:
// 1 <= len(A) <= 7e5
// 1 <= A[i] <= 1e7

// Examples:

// Input 1:
//     A = [1, 2]
// Output 1:
//     1
// Explanation:
//     Buy the stock on day 0, and sell it on day 1.

// Input 2:
//     A = [1, 4, 5, 2, 4]
// Output 2:
//     4
// Explanation:
//     Buy the stock on day 0, and sell it on day 2.

// Just process from the end to the beginning, always having a variable for the max element to 
// the right, and for the max diff 
int maxProfitSimple(const vector<int> &A) {
	int size = A.size();
	if(size < 2) {
		return 0;
	}

	int maxDiff = 0;
	int maxRightElement = A[size-1];
	for(int i = size-2; i >= 0; --i) {
		if(A[i] > maxRightElement) {
			maxRightElement = A[i];
		} else {
			maxDiff = max(maxDiff, maxRightElement-A[i]);
		}
	}

	return maxDiff;
}


// Version II of the problem:
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

// Say you have an array for which the ith element is the price of a given stock on day i.

// Design an algorithm to find the maximum profit. You may complete as many transactions 
// as you like (i.e., buy one and sell one share of the stock multiple times).

// Note: You may not engage in multiple transactions at the same time (i.e., you must sell the 
// stock before you buy again).

// Bottom-up:
int maxProfit(vector<int> &prices) {
	if(prices.empty()) {
		return 0;
	}

	int s = prices.size(); // .size() is unsigned, be careful when decrementing (eg: convert to int as here)
    vector<vector<int>> memo(2, vector<int>(s, 0));
	memo[1][s-1] = prices[s-1];
	for(int j = s-2; j >= 0; --j) {
		memo[0][j] = max(memo[0][j+1], memo[1][j+1]-prices[j]);
		memo[1][j] = max(memo[1][j+1], memo[0][j+1]+prices[j]);
	}

	return memo[0][0];
}
// You can even improve the memory (you only need the 2 states in the future to compute each past state)


// Version "with cooldown" of the problem:
// Remember: just skip one day after selling - simpler and elegant.
// https://neetcode.io/problems/buy-and-sell-crypto-with-cooldown
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown

// You are given an array prices where prices[i] is the price of a given stock on the ith day.
// Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and 
// sell one share of the stock multiple times) with the following restrictions:
// After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

// Example 1:
// Input: prices = [1,2,3,0,2]
// Output: 3
// Explanation: transactions = [buy, sell, cooldown, buy, sell]

// Top-down:
// O(N) in time and space.
// memo[i][j] gives the max profit from day "i" onwards with "has" indicating if you have or not the stock on day "i".
int maxProfitRecursive(const vector<int>& prices, int i, int has, vector<vector<int>>& memo) {
    if (i >= prices.size()) {
        return 0;
    }
    if (memo[has][i] != -1) {
        return memo[has][i];
    }

    if (has) {
        memo[has][i] =
            max(maxProfitRecursive(prices, i + 1, 1, memo),
                maxProfitRecursive(prices, i + 2, 0, memo) + prices[i]); // if you sell there is a cooldown of 1 day before you can choose to buy again.
    } else {
        memo[has][i] =
            max(maxProfitRecursive(prices, i + 1, 0, memo),
                maxProfitRecursive(prices, i + 1, 1, memo) - prices[i]);
    }

    return memo[has][i];
}

int maxProfit(vector<int>& prices) {
    vector<vector<int>> memo(2, vector<int>(prices.size(), -1));
    return maxProfitRecursive(prices, 0, 0, memo);
}

// Bottom-up:
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    // can_buy below is just basically indicating if it has or not the stock, not related to the 1-day cooldown, for 
    // that it just skips 1 day like above after selling the stock.
    for (int i = n - 1; i >= 0; --i) {
        for (int can_buy = 1; can_buy >= 0; --can_buy) {
            if (can_buy == 1) { // means it does not have the stock.
                int buy = dp[i + 1][0] - prices[i];
                int cooldown = dp[i + 1][1];
                dp[i][1] = max(buy, cooldown);
            } else { // means it has the stock so it cannot buy one more.
                int sell = (i + 2 < n) ? dp[i + 2][1] + prices[i] : prices[i];
                int cooldown = dp[i + 1][0]; // keeps the stock 1 more day.
                dp[i][0] = max(sell, cooldown);
            }
        }
    }

    return dp[0][1]; // from day 0 onwards, with can_buy set to 1 (since it does not start having the stock).
}


// Version III of the problem (allowed 2 transactions):
// See best_time_to_buy_and_sell_stocks_iii.cpp
// (Look for the top-down recursive solution there first, good for intuition - having one extra dimension 
// for has_stock and another for n_completed_operations - both with size 2).

int main() {
	// vector<int> A = {1, 2}; // ans: 1
	vector<int> A = {1, 4, 5, 2, 4}; // ans: 4 for simple, 6 for complex
	// vector<int> A = {7, 1, 5, 3, 6, 4}; // ans: 7 for complex
	cout << "Answer: " << maxProfit(A) << endl;

	return 0;
}