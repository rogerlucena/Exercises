#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/edit-distance/
// Dynamic Programming

// Given two strings A and B, find the minimum number of steps required to convert A to B. (each operation is counted as 1 step.)

// You have the following 3 operations permitted on a word:

// Insert a character
// Delete a character
// Replace a character

// Examples:
// Input 1:
//     A = "abad"
//     B = "abac"
// Output 1:
//     1
// Explanation 1:
//     Operation 1: Replace d with c.

// Input 2:
//     A = "Anshuman"
//     B = "Antihuman"
// Output 2:
//     2
// Explanation 2:
//     => Operation 1: Replace s with t.
//     => Operation 2: Insert i.


// Lessons: to do not deal with substrings generation, work with indexes!
// think simply, one step at a time, and memoize repeated work
int minDistance(string A, string B) {
	int n = A.size();
	int m = B.size();
	vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

	for(int i = 0; i <= n; ++i) {
		dp[i][0] = i;
	}
	for(int j = 0; j <= m; ++j) {
		dp[0][j] = j;
	}

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(A[i-1] == B[j-1]) {
				dp[i][j] = dp[i-1][j-1];
			} else {
				dp[i][j] = 1 + min({
					dp[i-1][j-1], // replace the i-th char of A
					dp[i][j-1], // insert the j-th char of B after the i-th char of A
					dp[i-1][j], // delete the i-th char of A
				});
			}
		}
	}

	return dp[n][m]; // taking the n first chars of A and the m first chars of B.
}

// Optimized to be O(A.size()) in space, still O(size1 * size2) in time
int minDistanceOptimized(string A, string B) {
	int r = A.size();
	int c = B.size();

	vector<int> prev(r+1, 0);
	for(int i = 1; i <= r; ++i) {
		prev[i] = i;
	}

	for(int j = 1; j <= c; ++j) {
		vector<int> dp(r+1, 0);
		dp[0] = j;
		for(int i = 1; i <= r; ++i) {
			if(A[i-1] == B[j-1]) {
				dp[i] = prev[i-1];
			} else {
				dp[i] = 1 + min({
					prev[i], // insert in A
					dp[i-1], // delete from A
					prev[i-1], // replace in A
				});
			}
		}
		// swap(prev, dp); // std::swap is O(n)
		prev.swap(dp); // vector::swap is O(1) (exchange the addresses/contens of the containers)
	}

	return prev[r];
}

// Lessons: to do not deal with substrings generation, work with indexes!
// below we have my solution, DP memoization + recursive stack size in memory too (but sill O(n*m) in memory).
int editDistance(string &s1, int index1, string &s2, int index2, vector<vector<int>> &m) {
	if(m[index1][index2] != -1) {
		return m[index1][index2];
	}

	if(index1 == s1.size() || index2 == s2.size()) {
		m[index1][index2] = max(s1.size() - index1, s2.size() - index2);
	} else {
		m[index1][index2] = s1[index1] == s2[index2] 
			? editDistance(s1, index1+1, s2, index2+1, m) 
			: min({
				1 + editDistance(s1, index1+1, s2, index2+1, m), // replace first char of s1 by the first of s2
				1 + editDistance(s1, index1+1, s2, index2, m), // delete first char of s1
				1 + editDistance(s1, index1, s2, index2+1, m) // insert at the beginning s1 first char of s2
			});
	}

	return m[index1][index2];
}

int myMinDistance(string A, string B) {
	if(A.size() == 0 || B.size() == 0) {
		return max(A.size(), B.size());
	}

	int len1 = A.size();
	int len2 = B.size();
	vector<vector<int>> m (len1+1, vector<int>(len2+1, -1));
	
	// Understand as the min # of operations to transform "A" from "index1" till its end on "B" from "index2" till its end 
	return editDistance(A, 0, B, 0, m);
}

int main() {
	// Answer expected: 1 
	// string A = "abad";
    // string B = "abac";

	// Answer expected: 2 
	string A = "Anshuman";
    string B = "Antihuman";

	cout << "Answer: " << minDistance(A, B) << endl;

	return 0;
}