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


int main() {
	// vector<int> A = {1, 2}; // ans: 1
	vector<int> A = {1, 4, 5, 2, 4}; // ans: 4
	cout << "Answer: " << maxProfit(A) << endl;

	return 0;
}