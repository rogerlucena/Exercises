#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/interleaving-strings
// https://neetcode.io/problems/interleaving-string
// https://leetcode.com/problems/interleaving-string
// 2D DP. This problem is interesting to visualize that it can have duplicate subproblems too! (not evident at first glance)
// For example, if we consider A = “XXX”, B = “XXX” and C = “XXXXXX” (imagine the 2D vector "m" and the recursion tree)
// obs: for the recursion in fact there was no need for "ic", we analyze here if "A" starting in "ia" and "B" starting 
// in "ib" can interleave generating "C" starting in "ia+ib" (which is the same as "ic", redundant).
// Note that for "From Neetcode and Leetcode" problem statement below, the 
// condition |#substrings_s - #substrings_t| <= 1 is automatically satisfied since whenever we do not get a char 
// from s we get from t (try to think mentally by contradiction finding a conter-example and you will see it is not possible).

// Given A, B, C, find whether C is formed by the interleaving of A and B.

// Constraints:
// 1 <= length(A), length(B), length(C) <= 150

// Examples in "main()"

// From Neetcode and Leetcode:
// Interleaving two strings s and t is done by dividing s and t into n and m substrings respectively, where the 
// following conditions are met |n - m| <= 1, i.e. the difference between the number of substrings of s and t is 
// at most 1.
// s = s1 + s2 + ... + sn
// t = t1 + t2 + ... + tm
// Interleaving s and t is s1 + t1 + s2 + t2 + ... or t1 + s1 + t2 + s2 + ...

// Top-down:
// O(M * N) in time and space by the end
// whithout memoization it would be exponential in the worst case -> O(2^n), n = M + N
int isInterleaveHelper(string &A, int ia, string &B, int ib, string &C, vector<vector<int>> &m) {
	// Memoization because there may be some overlapping situations
	// For example, if we consider A = “XXX”, B = “XXX” and C = “XXXXXX” 
	// and draw recursion tree, there will be many overlapping subproblems.
	if(m[ia][ib] != -1) {
		return m[ia][ib];
	}
	
	if(ia == A.size() && ib == B.size()) {
		m[ia][ib] = 1;
	} else {
        int ic = ia + ib;
        bool answer = false; 
		if (ia < A.size() && A[ia] == C[ic]) {
			answer |= isInterleaveHelper(A, ia + 1, B, ib, C, m);
		}
		if (!answer && ib < B.size() && B[ib] == C[ic]) {
			answer |= isInterleaveHelper(A, ia, B, ib + 1, C, m);
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
	return isInterleaveHelper(A, 0, B, 0, C, m);
}

// Bottom-up (from website):
bool isInterleaveBottomUp(string s1, string s2, string s3) {
	int m = s1.length(), n = s2.length();
	if (m + n != s3.length()) {
		return false;
	}

	vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
	dp[m][n] = true;

	for (int i = m; i >= 0; i--) {
		for (int j = n; j >= 0; j--) {
			if (i < m && s1[i] == s3[i + j] && dp[i + 1][j]) {
				dp[i][j] = true;
			}
			if (j < n && s2[j] == s3[i + j] && dp[i][j + 1]) {
				dp[i][j] = true;
			}
		}
	}
	return dp[0][0];
}

// Space optmized (from website) - just 2 vectors each time instead of a 2D matrix:
bool isInterleaveSpaceOptimized(string s1, string s2, string s3) {
	int m = s1.size(), n = s2.size();
	if (m + n != s3.size()) return false;
	if (n < m) {
		swap(s1, s2);
		swap(m, n);
	}

	vector<bool> dp(n + 1);
	dp[n] = true;
	for (int i = m; i >= 0; --i) {
		vector<bool> nextDp(n + 1);
		if (i == m) nextDp[n] = true;
		for (int j = n; j >= 0; --j) {
			if (i < m && s1[i] == s3[i + j] && dp[j]) {
				nextDp[j] = true;
			}
			if (j < n && s2[j] == s3[i + j] && nextDp[j + 1]) {
				nextDp[j] = true;
			}
		}
		dp = nextDp;
	}
	return dp[0];
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