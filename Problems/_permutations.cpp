#include <iostream>
#include <vector>
#include <algorithm>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/permutations/

// Given a collection of numbers, return all possible permutations.

// Example:
// With [1,2,3] we will have the following permutations:
// [1,2,3]
// [1,3,2]
// [2,1,3] 
// [2,3,1] 
// [3,1,2] 
// [3,2,1]

// NOTE:
// No two entries in the permutation sequence should be the same.
// For the purpose of this problem, assume that all the numbers in the collection are unique.

void auxPermute(vector<int> &A, int start, vector<vector<int>> &ans) {
	if(start == A.size() - 1) {
		ans.push_back(A);
		return;
	}

	for(int i = start; i < A.size(); ++i) {
		swap(A[start], A[i]);
		auxPermute(A, start+1, ans);
		swap(A[start], A[i]);
	}
}

vector<vector<int>> permute(vector<int> &A) {
	vector<vector<int>> ans;
	if(A.size() == 0) {
		return ans;
	}

	// sort(A.begin(), A.end());
	auxPermute(A, 0, ans);

	return ans;

}

int main() {
	vector<int> A = {1, 2, 3};
	for(vector<int> p : permute(A)) {
		printVector(p);
	}

	return 0;
}