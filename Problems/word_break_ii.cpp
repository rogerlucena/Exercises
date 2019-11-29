#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "tools.cpp"

// https://www.interviewbit.com/problems/word-break-ii/

// Given a string A and a dictionary of words B, add spaces in A to construct a sentence 
// where each word is a valid dictionary word.
// Return all such possible sentences.
// Note: Make sure the strings are sorted in your result.

// Constraints:
// 1 <= len(A) <= 50
// 1 <= len(B) <= 25
// 1 <= len(B[i]) <= 20

// Examples:

// Input 1:
//     A = "b"
//     B = ["aabbb"]
// Output 1:
//     []

// Input 2:
//     A = "catsanddog",
//     B = ["cat", "cats", "and", "sand", "dog"]
// Output 2:
//     ["cat sand dog", "cats and dog"]

using namespace std;

vector<string> wordBreakHelper(const string &A, unordered_set<string> &dict, int pos, vector<vector<string>> &memo) {
	if(pos < 0) {
		return vector<string>();
	}

	if(!memo[pos].empty()) {
		return memo[pos];
	}

	string currWord = A.substr(0, pos+1);
	if(dict.find(currWord) != dict.end()) {
		memo[pos].push_back(currWord);
	}

	for(int p = pos-1; p >= 0; --p) {
		currWord = A.substr(p+1, pos-p);
		if(dict.find(currWord) != dict.end()) {
			for(string prevAns : wordBreakHelper(A, dict, p, memo)) {
				string currAns = prevAns + " " + currWord;
				memo[pos].push_back(currAns);
			}
		}
	}

	if(pos == A.size()-1) {
		sort(memo[pos].begin(), memo[pos].end());
	}
	return memo[pos];
}

vector<string> wordBreak(string A, vector<string> &B) {
	unordered_set<string> dict;
	for(string w : B) {
		dict.insert(w);
	}

	vector<vector<string>> memo(A.size(), vector<string>());
	return wordBreakHelper(A, dict, A.size()-1, memo);
}


int main() {
	// string A = "b";
    // vector<string> B = {"aabbb"}; // ans: []

	string A = "catsanddog";
    vector<string> B = {"cat", "cats", "and", "sand", "dog"}; // ans: ["cat sand dog", "cats and dog"]

	auto printEl = [](const string &s) {cout << s;};
	printVector<string>(wordBreak(A, B), printEl);
	// printVector<string>({"aa", "bb"}, printEl);

	return 0;
}