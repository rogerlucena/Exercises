#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/alien-dictionary/

// Some words were ordered following an alphabetical order that is different from the normal one.
// Given these words, could you get the ordered alphabet that generated the order of the words?
// (mock with barra)

// assumptions: the input is always valid, no cycles (order inconsistency) etc ... then, DAG!
// Key idea: for each word "i" and "i+1" we can extract only one useful comparison information!
// Do that, you will get O(N-1) edges of a graph
// Do the topological sort in the graph, the order found is our wanted alphabet!
// 	 (obs: the alphabet may not be unique - in a given moment, or even at the beginning, we may have more than one char with 0 inDegree) 
pair<char, char> getCharsOrdered(const string &w1, const string &w2){
	for(int i = 0; i < w1.size() && i < w2.size(); ++i) {
		if(w1[i] != w2[i]) {
			return {w1[i], w2[i]};
		}
	}

	return {};
}

vector<char> getAlphabet(const vector<string> &words) {
	unordered_map<char, unordered_set<char>> relsGraph;
	for(string w : words) {
		for(char c : w) {
			relsGraph[c] = {};
		}
	}
	for(int i = 0; i <= int(words.size())-2; ++i) { // attention when doing .size() minus something! (unsigned int)
		pair<char, char> p = getCharsOrdered(words[i], words[i+1]);
		if(p != pair<char, char>({})) {
			// cout << p.first << " < " << p.second << endl;
			relsGraph[p.first].insert(p.second);
		}
	}

	// fill inDegrees
	unordered_map<char, int> inDegrees;
	for(pair<char, unordered_set<char>> rel : relsGraph) {
		if(inDegrees.find(rel.first) == inDegrees.end()) {
			inDegrees[rel.first] = 0;
		}
		for(char neigh : rel.second) {
			if(inDegrees.find(neigh) == inDegrees.end()) {
				inDegrees[neigh] = 0;
			}
			++inDegrees[neigh];
		}
	}

	// do the topo sort here
	queue<char> q;
	for(pair<char, int> pairCharDegree : inDegrees) {
		if(pairCharDegree.second == 0) {
			q.push(pairCharDegree.first);
		}
	}

	vector<char> alphabet;
	while(!q.empty()) {
		char curr = q.front();
		q.pop();
		alphabet.push_back(curr);
		for(char neigh : relsGraph[curr]) {
			if(--inDegrees[neigh] == 0) {
				q.push(neigh);
			}
		}
	}

	return alphabet.size() == relsGraph.size() ? alphabet : vector<char>({}); // empty vector if invalid input
}

int main() {
	vector<string> words = {"air", "car", "doodled", "doodleb", "doo", "doodle", "dooble"};
	// vector<string> words = {"wnlb"};
	for(char c : getAlphabet(words)) { // want: a, c, d, b
		cout << c << " ";
	}
	cout << endl;

	return 0;
}

// Another reference: https://www.geeksforgeeks.org/given-sorted-dictionary-find-precedence-characters/