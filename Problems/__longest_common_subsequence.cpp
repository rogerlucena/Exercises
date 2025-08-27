#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/longest-common-subsequence
// https://leetcode.com/problems/longest-common-subsequence

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

// Top-down:
// O(m*n) in time and space.
int longestCommonSubsequenceRecursive(const string& text1, int i, const string& text2, int j, vector<vector<int>>& memo) {
    if (i == text1.size() || j == text2.size()) {
        return 0;
    }
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    if (text1[i] == text2[j]) {
        memo[i][j] = 1 + longestCommonSubsequenceRecursive(text1, i + 1, text2,
                                                           j + 1, memo);
    } else {
        memo[i][j] = max(
            longestCommonSubsequenceRecursive(text1, i + 1, text2, j, memo),
            longestCommonSubsequenceRecursive(text1, i, text2, j + 1, memo));
    }

    return memo[i][j];
}

int longestCommonSubsequence(string text1, string text2) {
    vector<vector<int>> memo(text1.size(), vector<int>(text2.size(), -1));
    return longestCommonSubsequenceRecursive(text1, 0, text2, 0, memo);
}

// Bottom-up:
// Same complexity in time/space as above, but faster on leetcode percentage.
int longestCommonSubsequence(string text1, string text2) {
    vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1));

    for (int i = text1.size() - 1; i >= 0; i--) {
        for (int j = text2.size() - 1; j >= 0; j--) {
            if (text1[i] == text2[j]) {
                dp[i][j] = 1 + dp[i + 1][j + 1];
            } else {
                dp[i][j] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }

    return dp[0][0];
}

int main() {
	string text1 = "abcde", text2 = "ace"; // ans: 3
	// string text1 = "abc", text2 = "abc"; // ans: 3
	// string text1 = "abc", text2 = "def"; // ans: 0
	cout << "Answer: " << longestCommonSubsequence(text1, text2) << endl;

	return 0;
}