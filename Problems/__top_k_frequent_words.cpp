#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/top-k-frequent-words/

// Given a non-empty list of words, return the k most frequent elements.
// Your answer should be sorted by frequency from highest to lowest. If two words have the same
// frequency, then the word with the lower alphabetical order comes first.

// Key idea: remember to preprocess first to extract the Frequencies hash map, after that build your customized priority queue
// (remember the syntax for customized comparator)
vector<string> topKFrequent(vector<string>& words, int k) {
	// Extract frequencies.
	unordered_map<string, int> freqs;
	for (string w : words) {
		if (freqs.find(w) == freqs.end()) {
			freqs[w] = 1;
		} else {
			++freqs[w];
		}
	}
	
	// Build priority queue.
	auto cmp = [](const pair<string, int>& p1, const pair<string, int>& p2) {
		if (p1.second != p2.second) {
			return p1.second > p2.second;
		}
		return p1.first.compare(p2.first) < 0;
	};
	priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> mostFrequent(cmp);
	
	// Fill priority queue with "k" most frequent words.
	for (pair<string, int> wordFreq : freqs) {
		if (mostFrequent.size() < k) {
			mostFrequent.push(wordFreq);
			continue;
		}

		pair<string, int> top = mostFrequent.top();
		if(cmp(wordFreq, top)) {
			mostFrequent.pop();
			mostFrequent.push(wordFreq);
		}
	}
	
	// Build the final vector to be returned.
	vector<string> listMostFrequent;
	for (; !mostFrequent.empty(); mostFrequent.pop()) {
		pair<string, int> wordFreq = mostFrequent.top();
		listMostFrequent.push_back(wordFreq.first);
	}
	reverse(listMostFrequent.begin(), listMostFrequent.end());

	return listMostFrequent;
}

int main() {
	vector<string> words = {"i", "love", "leetcode", "i", "love", "coding"}; // ans: "i", "love" (alphabetical order)
	int k = 2;
	
	vector<string> words1 = {"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"}; // ans: "the", "is", "sunny", "day"
	int k2 = 4;

	vector<string> ans = topKFrequent(words, k);
	printVector(ans);

	return 0;
}