#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// https://leetcode.com/problems/longest-string-chain/

// Given a list of words, each word consists of English lowercase letters.
// Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to
// make it equal to word2.  For example, "abc" is a predecessor of "abac".
// A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, where word_1 is a predecessor of word_2,
// word_2 is a predecessor of word_3, and so on.
// Return the longest possible length of a word chain with words chosen from the given list of words.

// Below, could also have though about, sorting the list of words and then, for each word, try to find if you have previously
// seen another word obtained from removing one char from the current word -> O(NlogN + NSS) in time, O(NS) in space (S is max size of word = 16 here).
// Solution below is O(N^2) in time and probably in space too (build the graph).
bool isPredecessor(const string& w1, const string& w2) {
	if(w1.size() + 1 != w2.size()) {
		return false;
	}

	for (int i = 0, j = 0; i < w1.size(); ++i, ++j) {
		if(w1[i] != w2[j]) {
			if(i != j) {
				return false;
			}
			--i;
		}
	}

	return true;
}

void dfsFrom(const string& w, unordered_map<string, unordered_set<string>>& graph, unordered_map<string, int>& longestFrom) {
	int maxFromChildren = 0;
	for (string neigh : graph[w]) {
		if(longestFrom.find(neigh) == longestFrom.end()) {
			dfsFrom(neigh, graph, longestFrom);
		}
		maxFromChildren = max(maxFromChildren, longestFrom[neigh]);
	}
	
	longestFrom[w] = maxFromChildren + 1;
}

int longestStrChain(vector<string>& words) {
	// Build graph.
	unordered_map<string, unordered_set<string>> graph;
	for (int i = 0; i < words.size(); ++i) {
		for (int j = i+1; j < words.size(); ++j) {
			if (isPredecessor(words[i], words[j])) {
				graph[words[i]].insert(words[j]);
			} else if (isPredecessor(words[j], words[i])) {
				graph[words[j]].insert(words[i]);
			}
		}
	}

	// Retrieve longest path in graph through DFSs.
	unordered_map<string, int> longestFrom;
	int longestChain = 0;
	for (string w : words) {
		if (longestFrom.find(w) == longestFrom.end()) {
			dfsFrom(w, graph, longestFrom);
			longestChain = max(longestChain, longestFrom[w]);
		}
	}

	return longestChain;
}

int main() {
	vector<string> words = {"a","b","ba","bca","bda","bdca"}; // ans: 4
	int ans = longestStrChain(words);
	cout << "Answer: " << ans << endl;

	return 0;
}