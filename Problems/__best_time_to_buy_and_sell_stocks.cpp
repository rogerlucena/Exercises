#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/best-time-to-buy-and-sell-stocks-i/
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
int maxProfit(const vector<int> &A) {
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

int maxProfit(vector<int> &prices) {
	if(prices.empty()) {
		return 0;
	}

	int s = prices.size();
    vector<vector<int>> memo(2, vector<int>(s, 0));
	memo[1][s-1] = prices[s-1];
	for(int j = s-2; j >= 0; --j) {
		memo[0][j] = max(memo[0][j+1], memo[1][j+1]-prices[j]);
		memo[1][j] = max(memo[1][j+1], memo[0][j+1]+prices[j]);
	}

	return memo[0][0];
}
// You can even improve the memory (you only need the 2 states in the future to compute each past state)

int main() {
	// vector<int> A = {1, 2}; // ans: 1
	vector<int> A = {1, 4, 5, 2, 4}; // ans: 4
	cout << "Answer: " << maxProfit(A) << endl;

	return 0;
}