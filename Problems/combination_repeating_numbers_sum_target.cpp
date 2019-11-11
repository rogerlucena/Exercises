#include <iostream>
#include <vector>
#include <algorithm>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/combination-sum/

// Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where 
// the candidate numbers sums to T.

// The same repeated number may be chosen from C unlimited number of times.

//  Note:
// All numbers (including target) will be positive integers.
// Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
// The combinations themselves must be sorted in ascending order.
// CombinationA > CombinationB iff (a1 > b1) OR (a1 = b1 AND a2 > b2) OR … (a1 = b1 AND a2 = b2 
// AND … ai = bi AND ai+1 > bi+1)
// The solution set must not contain duplicate combinations.

// Example:
// Given candidate set 2,3,6,7 and target 7,
// A solution set is:
//    [2, 2, 3]
//    [7]

void auxCombinationSum(vector<int> &A, int target, int start, vector<int> &currVector, vector<vector<int>> &ans) {
	if(target == 0) {
		ans.push_back(currVector);
		return;
	} else if(start >= A.size()) {
		return;
	}

	for(int i = target/A[start]; i >= 1; --i) {
		currVector.push_back(A[start]);
	}

	int nextPos = start+1;
	while(nextPos < A.size() && A[start] == A[nextPos]) {
		++nextPos;
	}

	for(int i = target/A[start]; i >= 1; --i) {
		auxCombinationSum(A, target - i * A[start], nextPos, currVector, ans);
		currVector.pop_back();
	}

	auxCombinationSum(A, target, nextPos, currVector, ans);
}

vector<vector<int>> combinationSum(vector<int> &A, int B) {
	vector<vector<int>> ans;
	if(A.size() == 0) {
		return ans;
	}

	sort(A.begin(), A.end());
	vector<int> currVector;
	auxCombinationSum(A, B, 0, currVector, ans);

	return ans;
}


int main() {
	vector<int> A = {2, 3, 6, 7};
	int B = 7;

	for(vector<int> sol : combinationSum(A, B)) {
		printVector(sol);
	}

	return 0;
}