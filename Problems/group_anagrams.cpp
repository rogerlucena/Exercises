#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

#include "tools.cpp"

// https://leetcode.com/problems/group-anagrams/description/

// From a vector of strings, group all the anagrams together.

// Example:

// Input: ["eat", "tea", "tan", "ate", "nat", "bat"],

// Output:
// [
// ["ate","eat","tea"],
// ["nat","tan"],
// ["bat"]
// ]

using namespace std;

string genSignature(string s) {
    vector<int> occ(26, 0);
    string signature;
    for(char c : s) {
        occ[c-'a']++;
    }
    for(int i = 0; i < 26; ++i) {
        if(occ[i] > 0) {
            signature.push_back('a' + i); // ASCII
            ostringstream aux; 
			aux << occ[i];
            signature.append(aux.str());
        }
    }

    return signature;
}

// time: O(n*m), space: O(n*m)
vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> map;
    vector<vector<string>> solution;

    for(string s : strs) {
        string signature = genSignature(s);

        if(map.find(signature) != map.end()) {
            map[signature].push_back(s);
        } else {
            map[signature] = {s};
        }
    }

    for(pair<string, vector<string>> p : map) {
        solution.push_back(p.second);
    }

    return solution;
}

int main() {
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> solution = groupAnagrams(strs);

    for(const vector<string> vectorOfAnagrams : solution) {
		function<void(const string&)> printEl = [](const string &s) -> void {cout << s;};
        printVector(vectorOfAnagrams, printEl);
    }

    return 0;
}