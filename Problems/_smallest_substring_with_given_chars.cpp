#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// https://www.pramp.com/challenge/wqNo9joKG6IJm67B6z34
// Tricky

// Given an array of unique characters arr and a string str, Implement a function
// getShortestUniqueSubstring that finds the smallest substring of str containing all
// the characters in arr. Return "" (empty string) if such a substring doesn’t exist.

// Come up with an asymptotically optimal solution and analyze the time and space complexities.

// Example:
// input:  arr = ['x','y','z'], str = "xyyzyzyx"
// output: "zyx"

void addToAuxIfInSet(char c,
					 unordered_map<char, int> &aux,
					 unordered_set<char> &s) {

	if (s.find(c) != s.end()) {
		if (aux.find(c) != aux.end()) {
			aux[c] += 1;
		} else {
			aux[c] = 1;
		}
	}
}

string getShortestUniqueSubstring(const vector<char> &arr, const string &str) {
	// your code goes here
	unordered_map<char, int> aux;
	unordered_set<char> s;
	for (char c : arr) {
		s.insert(c);
	}

	int iSol = 0;
	int jSol = str.size() - 1;
	bool found = false;
	for (int i = 0, j = 0; i < str.size(); ++i) {
		char c = str[i];

		while (aux.size() != s.size() && j < str.size()) {
			addToAuxIfInSet(str[j++], aux, s);
		}

		if (aux.size() == s.size() && ((j - 1 - i) <= (jSol - iSol))) {
			iSol = i;
			jSol = j - 1;
			found = true;
		}

		if (aux.find(c) != aux.end()) {
			if (aux[c] == 1) {
				aux.erase(c);
			} else {
				--aux[c];
			}
		}
	}

	return found ? str.substr(iSol, jSol - iSol + 1) : "";
}

int main() {
	vector<char> arr = {'A', 'B', 'C'};
	string str = "ADOBECODEBANCDDD"; // ans: "BANC"
	
	cout << "Answer: " << getShortestUniqueSubstring(arr, str) << endl;

	return 0;
}