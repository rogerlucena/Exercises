#include <iostream>
#include <vector>
#include <unordered_map>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/substring-concatenation/

// You are given a string, S, and a list of words, L, that are all of the same length.

// Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters.

// Example:
// S: "barfoothefoobarman"
// L: ["foo", "bar"]
// You should return the indices: [0,9].
// (order does not matter).

bool isSolution(int index, const string &A, unordered_map<string, int> words, int nWords) {
	int len = (*words.begin()).first.size();

	for(int i = index; i < index + len * nWords; i += len) {
		string curr = A.substr(i, len);
		if(words.find(curr) == words.end()) {
			return false;
		}
		if(words[curr] == 1) {
			words.erase(curr);
		} else {
			--words[curr];
		}
	} 

	return words.empty();
}

vector<int> findSubstring(string A, const vector<string> &B) {
	if(B.empty()) {
		return vector<int>();
	}

	unordered_map<string, int> words;
	int nWords = 0;
	for(string w : B) {
		if(words.find(w) != words.end()) {
			++words[w];
		} else {
			words[w] = 1;
		}
		++nWords;
	}

	int len = B[0].size();
	if(A.size() < len * nWords) {
		return vector<int>();
	}

	vector<int> ans;
	for(int i = 0; i <= A.size() - len * nWords; ++i) {
		string curr = A.substr(i, len);
		if(words.find(curr) != words.end() && isSolution(i, A, words, nWords)) {
			ans.push_back(i);
		}
	}

	return ans;
}


int main() {
	string A = "barfoothefoobarman";
    vector<string> B = {"foo", "bar"}; // ans: {0, 9}

	// string A = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
 	// vector<string> B = {"aaa", "aaa", "aaa", "aaa", "aaa"}; // ans: {0, 1, ..., 98}

	// string A = "acbacbaacacbbcbacca";
	// vector<string> B = {"bccaaa", "acbcbb", "cbacba", "accaab", "bbacbb"}; // ans: {}

	// string A = "cacbbcabbacccacacaacacbbaccaabcbcbbcabbacc";
	// vector<string> B = {"b", "a", "b", "a", "c", "a", "b"}; // ans: {}

	vector<int> ans = findSubstring(A, B);
	printVector(ans);

	return 0;
}