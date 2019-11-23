#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

// https://www.interviewbit.com/problems/word-ladder-i/
// Think in graphs here!
// Use Djikstra only if weighted edges (and no negative edges!)
// Otherwise, a simple BFS will do the work :)

// Given two words A and B, and a dictionary, C, find the length of shortest transformation sequence from A to B, such that:

// You must change exactly one character in every transformation.
// Each intermediate word must exist in the dictionary.
// Note:

// Return 0 if there is no such transformation sequence.
// All words have the same length.
// All words contain only lowercase alphabetic characters.

// Constraints:
// 1 <= length(A), length(B), length(C[i]) <= 25
// 1 <= length(C) <= 5e3

// Example :
// Input:
//     A = "hit"
//     B = "cog"
//     C = ["hot", "dot", "dog", "lot", "log"]
// Output:
//     5
// Explanation:
//     "hit" -> "hot" -> "dot" -> "dog" -> "cog"

bool isOneStepAway(const string &s1, const string &s2) {
	int diff = 0;
	for(int i = 0; i < s1.size(); ++i) {
		if(s1[i] != s2[i]) {
			++diff;
		}
		if(diff > 1) {
			return false;
		}
	}

	return diff == 1;
}

int solve(string A, string B, vector<string> &C) {
	unordered_map<string, vector<string>> g;
	// C.push_back(A);
	// C.push_back(B);

	for(int i = 0; i < C.size(); ++i) {
		if(g.find(C[i]) == g.end()) {
			g[C[i]] = {};
		}
		for(int j = i+1; j < C.size(); ++j) {
			if(isOneStepAway(C[i], C[j])) {
				g[C[i]].push_back(C[j]);
				if(g.find(C[j]) == g.end()) {
					g[C[j]] = {};
				}
				g[C[j]].push_back(C[i]);
			}
		}
	}

	queue<pair<string, int>> q; // node and level
	unordered_set<string> enqueued;
	q.push({A, 0});
	enqueued.insert(A);
	while(!q.empty()) {
		pair<string, int> p = q.front();
		q.pop();
		string node = p.first;
		cout << node << endl;
		int level = p.second;
		if(node == B) {
			return level+1; // length of the complete path
		}
		for(string neigh : g[node]) {
			if(enqueued.find(neigh) == enqueued.end()) {
				q.push({neigh, level+1});
				enqueued.insert(neigh);
			}
		}	
	}

	return 0;
}


int main() {
	string A = "ymain";
	string B = "oecij";
    vector<string> C = {"ymann", "yycrj", "oecij", "ymcnj", "yzcrj", "yycij", "xecij", "yecij", "ymanj", "yzcnj", "ymain"};
	cout << "Answer: " << solve(A, B, C) << endl;

	return 0;
}