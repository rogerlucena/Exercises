#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/anagrams/

// Given an array of strings, return all groups of strings that are anagrams. Represent a group 
// by a list of integers representing the index in the original list. Look at the sample case for clarification.

// Anagram: a word, phrase, or name formed by rearranging the letters of another, such as 'spar', formed from 'rasp' 
// Note: All inputs will be in lower-case. 

// Example :
// Input : cat dog god tca
// Output : [[1, 4], [2, 3]]

vector<vector<int>> anagrams(const vector<string> &A) {
	vector<vector<int>> ans;

	unordered_map<string, vector<int>> m;
	for(int i = 1; i <= A.size(); ++i) {
		string currS = A[i-1];

		string id (currS);
		sort(id.begin(), id.end());

		if(m.find(id) != m.end()) {
			m[id].push_back(i);
		} else {
			m[id] = {i};
		}
	}

	for(pair<string, vector<int>> p : m) {
		ans.push_back(p.second);
	}

	return ans;
}


int main() {
	vector<string> A = {"cat", "dog", "god", "tca"};
	for(vector<int> v : anagrams(A)) {
		printVector(v);
	}

	return 0;
}