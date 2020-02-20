#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// https://leetcode.com/problems/word-break/
// DP, think recursion and then reuse previous work

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

bool wordBreakAux(const string &s, unordered_set<string> &dict, int start, vector<int> &memo) {
	if(memo[start] != -1) {
		return memo[start];
	}

	// cout << "start: " << start << endl;

	memo[start] = 0;
	for(int l = 1; l <= s.size() - start && !memo[start]; ++l) {
		string w = s.substr(start, l);
		if(dict.find(w) == dict.end()) {
			continue;
		}

		memo[start] = l == s.size() - start ? true : wordBreakAux(s, dict, start+l, memo);
	}

	return memo[start];
}

bool wordBreak(string s, vector<string> &wordDict) {
	if(s.empty()) {
		return false;
	}

	unordered_set<string> dict(wordDict.begin(), wordDict.end());
	vector<int> memo(s.size(), -1);

	return wordBreakAux(s, dict, 0, memo);
}

int main() {
	string s = "leetcode";
	vector<string> wordDict = {"leet", "code"}; // true

	cout << "Answer: " << wordBreak(s, wordDict) << endl;

	return 0;
}