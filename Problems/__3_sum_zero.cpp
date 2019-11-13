#include <iostream>
#include <vector>
#include <algorithm>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/3-sum-zero/
// (two pointer idea again)

// Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0?
// Find all unique triplets in the array which gives the sum of zero.

// Note:
// Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
// The solution set must not contain duplicate triplets. For example, given array S = {-1 0 1 2 -1 -4}, A solution set is:
// (-1, 0, 1)
// (-1, -1, 2)

int incrementTillDifferent(int j, vector<int> &A) {
	while(A[j+1] == A[j]) {
		++j;
	}
	return j+1;
}

int decrementTillDifferent(int k, vector<int> &A) {
	while(A[k-1] == A[k]) {
		--k;
	}
	return k-1;
}

vector<vector<int>> threeSum(vector<int> &A) {
	vector<vector<int>> ans = {};
	if(A.size() < 3) {
		return ans;
	}

	sort(A.begin(), A.end()); // A = {-4, -1, -1, 0, 1, 2}
	for(int i = 0; i < A.size()-2; i = incrementTillDifferent(i, A)) {
		int a = A[i];
		for(int j = i+1, k = A.size()-1; j < k; ) {
			int b = A[j];
			int c = A[k];
			int sum = a + b + c;
			if(sum == 0) {
				vector<int> ansElement = {a, b, c};
				ans.push_back(ansElement);
				j = incrementTillDifferent(j, A);
				k = decrementTillDifferent(k, A);
			} else if(sum < 0) {
				j = incrementTillDifferent(j, A);
			} else {
				k = decrementTillDifferent(k, A);
			}
		}
	}

	return ans;
}


int main() {
	vector<int> S = {-1, 0, 1, 2, -1, -4};
	cout << "Answer:" << endl;
	printMatrix(threeSum(S));
	return 0;
}