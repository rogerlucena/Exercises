#include <iostream>
#include <vector>

using namespace std;

// https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/

// Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total 
// value in the knapsack. 
// In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent 
// values and weights associated with n items respectively. Also given an integer W which represents knapsack capacity, 
// find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W

// Iterative KnapSack
int knapSack(int capacity, vector<int> &weights, vector<int> &val) {
	if(weights.size() == 0) {
		return 0;
	}

	// memo[i][j] = the max value possible using from position "i" on and current "weight" filled is j
	vector<vector<int>> memo(weights.size()+1, vector<int>(capacity +1 , -1));

	for(int i = weights.size(); i >= 0; --i) {
		for(int j = capacity; j >= 0; --j) {
			if(i == weights.size() || j == capacity) {
				memo[i][j] = 0;
			} else {
				memo[i][j] = memo[i+1][j]; // skip val[i]
				if(j + weights[i] <= capacity) {
					memo[i][j] = max(memo[i][j], val[i] + memo[i+1][j+weights[i]]); // uses val[i]
				}
			}
		}
	}

	return memo[0][0];
}

// Recursive KnapSack below
int knapSackHelper(int capacity, vector<int> &weights, vector<int> &val, int pos, int currWeight, vector<vector<int>> &memo) {
	if(pos == weights.size()) {
		return 0;
	}
	
	if(memo[pos][currWeight] != -1) {
		return memo[pos][currWeight];
	}

	memo[pos][currWeight] = knapSackHelper(capacity, weights, val, pos+1, currWeight, memo);
	if(currWeight + weights[pos] <= capacity) {
		memo[pos][currWeight] = max(memo[pos][currWeight], val[pos] + knapSackHelper(capacity, weights, val, pos+1, currWeight+weights[pos], memo));
	}

	return memo[pos][currWeight];
}

int recursiveKnapSack(int capacity, vector<int> &weights, vector<int> &val) {
	vector<vector<int>> memo(weights.size(), vector<int>(capacity+1 , -1));
	return knapSackHelper(capacity, weights, val, 0, 0, memo);
}

int main() {
	// vector<int> weights = {1, 1, 1};
	// vector<int> val = {10, 20, 30};
	// int capacity = 2; // ans: 50

    vector<int> weights = {10, 20, 30}; 
	vector<int> val = {60, 100, 120}; 
    int  capacity = 50; // ans: 220

	cout << "Answer: " << knapSack(capacity, weights, val) << endl;

	return 0;
}