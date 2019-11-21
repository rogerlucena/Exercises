#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/best-time-to-buy-and-sell-stocks-iii/

// Say you have an array, A, for which the ith element is the price of a given stock on day i.
// Design an algorithm to find the maximum profit. You may complete at most 2 transactions.
// Return the maximum possible profit.
// Note: You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

// Constraints:
// 1 <= length(A) <= 7e5
// 1 <= A[i] <= 1e7
// Examples:

// Input 1:
//     A = [1, 2, 1, 2]
// Output 1:
//     2
// Explanation 1: 
//     Day 0 : Buy 
//     Day 1 : Sell
//     Day 2 : Buy
//     Day 3 : Sell

// Input 2:
//     A = [7, 2, 4, 8, 7]
// Output 2:
//     6
// Explanation 2:
//     Day 1 : Buy
//     Day 3 : Sell

// Website solution:
// f[k, ii] represents the max profit up until prices[ii] (Note: NOT ending with prices[ii]) using at most k transactions. 
// f[k, ii] = max(f[k, ii-1], prices[ii] - prices[jj] + f[k-1, jj]) for jj in range of [0, ii-1] 
//          = max(f[k, ii-1], prices[ii] + max(f[k-1, jj] - prices[jj]) for jj in range of [0, ii-1] )
// f[0, ii] = 0; 0 times transaction makes 0 profit
// f[k, 0] = 0; if there is only one price data point you can't make any money no matter how many times you can trade
int maxProfit(vector<int> &A) {
	if (A.size() <= 1) {
		return 0;
	}

	int K = 2; // max number of transactions allowed
	int maxProf = 0;
	vector<vector<int>> f(K+1, vector<int>(A.size(), 0));

	for (int kk = 1; kk <= K; ++kk) {
		int tmpMax = f[kk-1][0] - A[0];
		for (int ii = 1; ii < A.size(); ii++) {
			f[kk][ii] = max(f[kk][ii-1], A[ii] + tmpMax);
			tmpMax = max(tmpMax, f[kk-1][ii] - A[ii]); // for paying the minimum to have a stock in hands right now
			maxProf = max(f[kk][ii], maxProf);
		}
	}
		
	return maxProf;
}

// My old solution (not that space efficient) below:
int maxProfitHelper(const vector<int> &A, int nCompletedOperations, int hasStock, int pos, vector<vector<vector<int>>> &memo) {
	if(nCompletedOperations == 2 || pos == A.size()) {
		return 0;
	}

	if(memo[nCompletedOperations][hasStock][pos] != -1) {
		return memo[nCompletedOperations][hasStock][pos];
	}

	if(hasStock) {
		memo[nCompletedOperations][hasStock][pos] = max(maxProfitHelper(A, nCompletedOperations,   1, pos+1, memo), 
													    maxProfitHelper(A, nCompletedOperations+1, 0, pos+1, memo) + A[pos]);
	} else {
		memo[nCompletedOperations][hasStock][pos] = max(maxProfitHelper(A, nCompletedOperations, 0, pos+1, memo), 
													    maxProfitHelper(A, nCompletedOperations, 1, pos+1, memo) - A[pos]);
	}

	return memo[nCompletedOperations][hasStock][pos];
}

int oldMaxProfit(const vector<int> &A) {
	int size = A.size();
	if(A.size() < 2) {
		return 0;
	}

	vector<vector<vector<int>>> memo(2, vector<vector<int>>(2, vector<int>(size, -1)));
	
	return maxProfitHelper(A, 0, 0, 0, memo);
}

int main() {
	// vector<int> A = {1, 2, 1, 2}; // ans: 2
	vector<int> A = {7, 2, 4, 8, 7}; // ans: 6
	cout << "Answer: " << maxProfit(A) << endl;

	return 0;
}