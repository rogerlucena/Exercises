#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// https://leetcode.com/problems/longest-word-in-dictionary/
// (Example of Trie instead of sort/hash-map to optimize performance)

// Given a list of strings words representing an English Dictionary, find the longest word in words that
// can be built one character at a time by other words in words. If there is more than one possible answer, return
// the longest word with the smallest lexicographical order.
// If there is no answer, return the empty string.

// Example:
// Input: 
// words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
// Output: "apple"
// Explanation: 
// Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".

// Solution below is O(N*L), where L is the size of the largest word (30 here).
// Another solution: sort the words by size, smaller first, go through filling a hash map with the words that can be built and
	// updating the longestWord as we go - O(N log N) in time
// Other solution: go through and add to hash map, then go through again verifying if all prefixes are in hash map - O(N*L^2).
	// the ^2 comes from generating all prefixes for each word.
class Trie {
	bool isEnd;
	unordered_map<char, Trie*> children;
public:
	Trie() {
		isEnd = false;
		children = {};
	}

	void insert(const string& word) {
		Trie* curr = this;
		for (char c : word) {
			if (curr->children.find(c) == curr->children.end()) {
				curr->children[c] = new Trie();
			}
			curr = curr->children[c];
		}
		curr->isEnd = true;
	}

	string longestGradativePath(string& currPath) {
		string maxPath = currPath;

		for(pair<char, Trie*> charChild : this->children) {
			char c = charChild.first;
			Trie* child = charChild.second;

			if (child->isEnd) {
				currPath.push_back(c);
				string candidate = child->longestGradativePath(currPath);

				if (candidate.size() > maxPath.size() || 
					(candidate.size() == maxPath.size() && candidate.compare(maxPath) < 0)) {
						maxPath = candidate;
				}
				currPath.pop_back();
			}
		}

		return maxPath;
	}
};

// With Trie.
// Runtime better than ~50%, memory ~50% too.
string longestWordTrie(vector<string>& words) {
	Trie* t = new Trie();
	for (string w : words) {
		t->insert(w);
	}

	string currPath = "";
	return t->longestGradativePath(currPath);
}

// Using only hash set. 
// Runtime better than 89.63% (better than trie), memory 76,12% (worse than trie - because of the hash set).
string longestWord(vector<string>& words) {
	unordered_set<string> canBuild;
	auto cmp = [](const string& s1, const string& s2) {
		if (s1.size() == s2.size()) {
			return s1.compare(s2) < 0;
		}

		return s1.size() < s2.size();
	};
	sort(words.begin(), words.end(), cmp);

	string longest = "";
	for (string w : words) {
		string prefix = w.substr(0, w.size()-1);
		if (w.size() == 1 || canBuild.find(prefix) != canBuild.end()) {
			canBuild.insert(w);
			longest = w.size() > longest.size() ? w : longest;
		}
	}

	return longest;
}

int main() {
	vector<string> words1 = {"w","wo","wor","worl", "world"}; // ans: "world"
	vector<string> words = {"a", "banana", "app", "appl", "ap", "apply", "apple"}; // ans: "apple"
	
	string ans = longestWord(words);
	cout << "Answer: " << ans << endl;

	return 0;
}