#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/distinct-subsequences/

// Given two sequences A, B, count number of unique ways in sequence A, to form a subsequence that is identical to the sequence B.

// Subsequence : A subsequence of a string is a new string which is formed from the original 
// string by deleting some (can be none) of the characters without disturbing the relative positions 
// of the remaining characters. (ie, “ACE” is a subsequence of “ABCDE” while “AEC” is not).

// Constraints:
// 1 <= length(A), length(B) <= 700

// Examples in main()

int numDistinctHelper(string &A, int ia, string &B, int ib, vector<vector<int>> &m) {
	if(m[ia][ib] != -1) {
		return m[ia][ib];
	}

	if(ia == A.size()) {
		m[ia][ib] = ib == B.size() ? 1 : 0;
	} else if(ib == B.size()) {
		m[ia][ib] = 1;
	} else if(B[ib] == A[ia]) {
		m[ia][ib] = numDistinctHelper(A, ia+1, B, ib+1, m) + numDistinctHelper(A, ia+1, B, ib, m);
	} else {
		m[ia][ib] =  numDistinctHelper(A, ia+1, B, ib, m);
	}

	return m[ia][ib];
}

int numDistinct(string A, string B) {
	if(A.size() < B.size()) {
		return false;
	}	

	// Memoization useful in the case we have repeated chars for example - overlapping subproblems
	vector<vector<int>> m (A.size()+1, vector<int>(B.size()+1, -1));

	return numDistinctHelper(A, 0, B, 0, m);
}

int main() {
	// Answer expected: 1
	// string A = "abc";
    // string B = "abc";

	// Answer expected: 3
	string A = "rabbbit"; 
    string B = "rabbit";

	cout << "Answer: " << numDistinct(A, B) << endl;
	return 0;
}