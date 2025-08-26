#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// https://neetcode.io/problems/word-break
// https://leetcode.com/problems/word-break 
// 1D DP, think recursion and then reuse previous work. Recursion tends to be more intuitive, Xandão likes it better as well.
// Remember: ok for complexity to be O(n * m * t) here depending also on t the max len of a word in dict.

// Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, 
// determine if s can be segmented into a space-separated sequence of one or more dictionary words.

// Note:
// The same word in the dictionary may be reused multiple times in the segmentation.
// You may assume the dictionary does not contain duplicate words.

// Example 1:
// Input: s = "leetcode", wordDict = ["leet", "code"]
// Output: true
// Explanation: Return true because "leetcode" can be segmented as "leet code".

// Example 2:
// Input: s = "applepenapple", wordDict = ["apple", "pen"]
// Output: true
// Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
//              Note that you are allowed to reuse a dictionary word.

// O(n * m * t) in time, O(n) in space - where n is len(s), m is len(wordDict) and t is max length of any word in wordDict.
bool wordBreakRecursive(const string& s, int i, const vector<string>& wordDict, vector<int>& memo) {
    if (i == s.size()) {
        return true;
    }
    if (memo[i] != -1) {
        return memo[i];
    }

    bool res = false;
    for (const string& word : wordDict) {
        if (i + word.size() > s.size() || s.substr(i, word.size()) != word) {
            continue;
        }
        if (wordBreakRecursive(s, i + word.size(), wordDict, memo)) {
            res = true;
            break;
        }
    }

    memo[i] = res == true ? 1 : 0;
    return res;
}

bool wordBreak(string s, vector<string>& wordDict) {
    vector<int> memo(s.size(), -1);
    return wordBreakRecursive(s, 0, wordDict, memo);
}

// Bottom-up:
// Same complexity as above.
bool wordBreak(string s, vector<string>& wordDict) {
    vector<bool> dp(s.size() + 1, false);
    dp[s.size()] = true;

    for (int i = s.size() - 1; i >= 0; i--) {
        for (const auto& w : wordDict) {
            if ((i + w.size()) <= s.size() &&
                    s.substr(i, w.size()) == w) {
                dp[i] = dp[i + w.size()];
            }
            if (dp[i]) {
                break;
            }
        }
    }

    return dp[0];
}

int main() {
	string s = "leetcode";
	vector<string> wordDict = {"leet", "code"}; // true

	cout << "Answer: " << wordBreak(s, wordDict) << endl;

	return 0;
}