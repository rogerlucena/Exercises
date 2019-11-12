#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/combinations/

// Given two integers n and k, return all possible combinations of k numbers out of 1 2 3 ... n.
// Make sure the combinations are sorted.

// To elaborate,
// Within every entry, elements should be sorted. [1, 4] is a valid entry while [4, 1] is not.
// Entries should be sorted within themselves.

// Example :
// If n = 4 and k = 2, a solution is:
// [
//   [1,2],
//   [1,3],
//   [1,4],
//   [2,3],
//   [2,4],
//   [3,4],
// ]

void auxCombine(int n, int k, vector<int> currVector, int curr, vector<vector<int>> &ans) {
	if(currVector.size() == k) {
		ans.push_back(currVector);
		return;
	}

	for(int i = curr; i <= n; ++i) {
		currVector.push_back(i);
		auxCombine(n, k, currVector, i+1, ans);
		currVector.pop_back();
	}
}

vector<vector<int>> combine(int A, int B) {
	vector<vector<int>> ans;
	vector<int> currVector;
	auxCombine(A, B, currVector, 1, ans);

	return ans;
}

int main() {
	int A = 4;
	int B = 2;
	for(vector<int> v : combine(A, B)) {
		printVector(v);
	}

	return 0;
}