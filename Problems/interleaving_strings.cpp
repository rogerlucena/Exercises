#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/interleaving-strings/

// Given A, B, C, find whether C is formed by the interleaving of A and B.

// Constraints:
// 1 <= length(A), length(B), length(C) <= 150

// Examples in "main()"

// O(M * N) in time and space by the end
// whithout memoization it would be exponential in the worst case -> O(2^n), n = M + N
int isInterleaveHelper(string &A, int ia, string &B, int ib, string &C, int ic, vector<vector<int>> &m) {
	// cout << "ia, ib, ic: " << ia << ", " << ib << ", " << ic << ", " << endl;
	if(ia == A.size() && ib == B.size()) {
		return ic == C.size();
	}

	if(ic >= C.size()) {
		return false;
	}

	// Memoization because there may be some overlapping situations
	// For example, if wee consider A = “XXX”, B = “XXX” and C = “XXXXXX” 
	// and draw recursion tree, there will be many overlapping subproblems.
	if(m[ia][ib] != -1) {
		return m[ia][ib];
	}

	bool answer = false; 
    if (ia < A.size() && A[ia] == C[ic]) {
		answer = answer || isInterleaveHelper(A, ia + 1, B, ib, C, ic + 1, m);
	}
	if (ib < B.size() && B[ib] == C[ic]) {
		answer = answer || isInterleaveHelper(A, ia, B, ib + 1, C, ic + 1, m);
	}
	m[ia][ib] = answer;

	return m[ia][ib];
}

int isInterleave(string A, string B, string C) {
	// Let us create a 2D table to store solutions of 
    // subproblems. m[i][j] will be true if C[0..i+j-1] 
    // is an interleaving of A[0..i-1] and B[0..j-1]. 
	vector<vector<int>> m(A.size()+1, vector<int>(B.size()+1, -1));
	return isInterleaveHelper(A, 0, B, 0, C, 0, m);
}

int main() {
	// Answer expected: 1
	// string A = "aabcc";
    // string B = "dbbca";
    // string C = "aadbbcbcac";

	// Answer expected: 0
	string A = "aabcc";
    string B = "dbbca";
    string C = "aadbbbaccc";

	cout << "Answer: " << isInterleave(A, B, C) << endl;

	return 0;
}