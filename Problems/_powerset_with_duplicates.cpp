#include <iostream>
#include <vector>
#include <algorithm>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/subsets-ii/

// Given a collection of integers that might contain duplicates, S, return all possible subsets.

// Note:
// Elements in a subset must be in non-descending order.
// The solution set must not contain duplicate subsets.
// The subsets must be sorted lexicographically.

// If S = [1,2,2], the solution is:
// [
// [],
// [1],
// [1,2],
// [1,2,2],
// [2],
// [2, 2]
// ]

void auxSubsetsWithDup(vector<int> &A, vector<int> &currVector, int index, vector<vector<int>> &ans) {
	ans.push_back(currVector);

	for(int i = index; i < A.size(); ++i) {
		currVector.push_back(A[i]);
		auxSubsetsWithDup(A, currVector, i+1, ans);
		currVector.pop_back();

		while(i+1 < A.size() && A[i+1] == A[i]) {
			++i;
		}
	}
}

vector<vector<int>> subsetsWithDup(vector<int> &A) {
	vector<vector<int>> ans = {};

	sort(A.begin(), A.end());
	vector<int> currVector = {};
	auxSubsetsWithDup(A, currVector, 0, ans);

	return ans;
}


int main() {
	vector<int> A = {1, 2, 3};
	vector<vector<int>> ans = subsetsWithDup(A);

	for(vector<int> v : ans) {
		printVector(v);
	}

	return 0;
}