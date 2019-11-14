#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/interleaving-strings/
// DP. This problem is interesting to visualize that it can have duplicate subproblems too! (not evident at first glance)
// For example, if we consider A = “XXX”, B = “XXX” and C = “XXXXXX” (imagine the 2D vector "m" and the recursion tree)

// Given A, B, C, find whether C is formed by the interleaving of A and B.

// Constraints:
// 1 <= length(A), length(B), length(C) <= 150

// Examples in "main()"

// O(M * N) in time and space by the end
// whithout memoization it would be exponential in the worst case -> O(2^n), n = M + N
int isInterleaveHelper(string &A, int ia, string &B, int ib, string &C, int ic, vector<vector<int>> &m) {
	// Memoization because there may be some overlapping situations
	// For example, if we consider A = “XXX”, B = “XXX” and C = “XXXXXX” 
	// and draw recursion tree, there will be many overlapping subproblems.
	if(m[ia][ib] != -1) {
		return m[ia][ib];
	}
	
	if(ia == A.size() && ib == B.size()) {
		m[ia][ib] = ic == C.size();
	} else if(ic == C.size()) {
		m[ia][ib] = false;
	} else {
		bool answer = false; 
		if (ia < A.size() && A[ia] == C[ic]) {
			answer = answer || isInterleaveHelper(A, ia + 1, B, ib, C, ic + 1, m);
		}
		if (ib < B.size() && B[ib] == C[ic]) {
			answer = answer || isInterleaveHelper(A, ia, B, ib + 1, C, ic + 1, m);
		}
		m[ia][ib] = answer;
	}

	return m[ia][ib];
}

int isInterleave(string A, string B, string C) {
	if(C.size() != A.size() + B.size()) {
		return false;
	}

	// Let us create a 2D table to store solutions of 
    // subproblems. m[i][j] will be true if C[i+j..end] 
    // is an interleaving of A[i..end] and B[j..end]. 
	// (note that we still have i+j chars from A and B to try to interleave and form the first i+j chars of C)
	vector<vector<int>> m (A.size()+1, vector<int>(B.size()+1, -1));
	return isInterleaveHelper(A, 0, B, 0, C, 0, m);
}

int main() {
	// Answer expected: 1
	string A = "aabcc";
    string B = "dbbca";
    string C = "aadbbcbcac";

	// Answer expected: 0
	// string A = "aabcc";
    // string B = "dbbca";
    // string C = "aadbbbaccc";

	cout << "Answer: " << isInterleave(A, B, C) << endl;

	return 0;
}