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
int editDistance(string &s1, int index1, string &s2, int index2, vector<vector<int>> &m) {
	if(index1 == s1.size() || index2 == s2.size()) {
		return max(s1.size() - index1, s2.size() - index2);
	}

	if(m[index1][index2] != -1) {
		return m[index1][index2];
	}

	m[index1][index2] = s1[index1] == s2[index2] 
		? editDistance(s1, index1+1, s2, index2+1, m) 
		: min({
			1 + editDistance(s1, index1+1, s2, index2+1, m), // replace first char of s1 by the first of s2
			1 + editDistance(s1, index1+1, s2, index2, m), // delete first char of s1
			1 + editDistance(s1, index1, s2, index2+1, m) // insert at the beginning s1 first char of s2
		});

	return m[index1][index2];
}

int minDistance(string A, string B) {
	if(A.size() == 0 || B.size() == 0) {
		return max(A.size(), B.size());
	}

	int len1 = A.size();
	int len2 = B.size();
	vector<vector<int>> m (len1, vector<int>(len2, -1));
	
	return editDistance(A, 0, B, 0, m);
}

int main() {
	// string A = "abad";
    // string B = "abac";
	string A = "Anshuman";
    string B = "Antihuman";

	cout << "Answer: " << minDistance(A, B) << endl;

	return 0;
}