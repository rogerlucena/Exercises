#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/longest-common-subsequence/

// Given two strings text1 and text2, return the length of their longest common subsequence.

// A subsequence of a string is a new string generated from the original string with some 
// characters (can be none) deleted without changing the relative order of the remaining 
// characters. (eg, "ace" is a subsequence of "abcde" while "aec" is not). A common subsequence of 
// two strings is a subsequence that is common to both strings.

// If there is no common subsequence, return 0.

// Example:
// Input: text1 = "abcde", text2 = "ace" 
// Output: 3  
// Explanation: The longest common subsequence is "ace" and its length is 3.

void fillMemo(const string &text1, const string &text2, vector<vector<int>> &memo) {
	for(int i = text1.size() - 1; i >= 0; --i) {
		for(int j = text2.size() - 1; j >= 0; --j) {
			if(text1[i] == text2[j]) {
				memo[i][j] = 1 + memo[i+1][j+1];
			} else {
				memo[i][j] = max(memo[i+1][j], memo[i][j+1]);
			}
		}
	}
}

int longestCommonSubsequence(string text1, string text2) {
	if(text1.empty() || text2.empty()) {
		return 0;
	}

	vector<vector<int>> memo(text1.size()+1, vector<int>(text2.size()+1, 0));
	fillMemo(text1, text2, memo);

	return memo[0][0];
}

int main() {
	string text1 = "abcde", text2 = "ace"; // ans: 3
	// string text1 = "abc", text2 = "abc"; // ans: 3
	// string text1 = "abc", text2 = "def"; // ans: 0
	cout << "Answer: " << longestCommonSubsequence(text1, text2) << endl;

	return 0;
}