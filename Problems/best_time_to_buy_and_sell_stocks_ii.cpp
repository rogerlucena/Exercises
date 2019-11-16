#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/best-time-to-buy-and-sell-stocks-ii/

// Say you have an array, A, for which the ith element is the price of a given stock on day i.

// Design an algorithm to find the maximum profit.

// You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).

// However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

// Example :

// Input 1:
//     A = [1, 2, 3]

// Output 1:
//     2

// Explanation 1:
//     => Buy a stock on day 0.
//     => Sell the stock on day 1. (Profit +1)
//     => Buy a stock on day 1.
//     => Sell the stock on day 2. (Profit +1)
    
//     Overall profit = 2

// Input 2:
//     A = [5, 2, 10]

// Output 2:
//     8

// Explanation 2:
//     => Buy a stock on day 1.
//     => Sell the stock on on day 2. (Profit +8)
    
//     Overall profit = 8

int maxProfitHelper(const vector<int> &A, int i, int j, vector<vector<int>> &memo) {
	if(memo[i][j] != -1) {
		return memo[i][j];
	}
	
	if(j == A.size()) {
		memo[i][j] = 0;
	} else if(i == 0) {
		memo[i][j] = max(maxProfitHelper(A, i, j+1, memo), maxProfitHelper(A, 1, j+1, memo) - A[j]);
	} else {
		memo[i][j] = max(maxProfitHelper(A, i, j+1, memo), maxProfitHelper(A, 0, j+1, memo) + A[j]);
	}

	// cout << endl << "(i, j): (" << i << ", " << j << ")" << endl;
	// printVector(A);
	// printMatrix(memo);
	return memo[i][j];
}

int maxProfit(const vector<int> &A) {
	if(A.size() < 2) {
		return 0;
	}

	vector<vector<int>> memo(2, vector<int>(A.size()+1, -1));
	return maxProfitHelper(A, 0, 0, memo);
}


int main() {
	vector<int> A = {1, 2, 3}; // ans: 2
	// vector<int> A = {5, 2, 10}; // ans: 8

	cout << "Answer: " << maxProfit(A) << endl;

	return 0;
}