#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

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

// Constraints:
// 1 <= strs.length <= 10^4
// 0 <= strs[i].length <= 100
// strs[i] consists of lowercase English letters.


// Time Complexity below: O(n*m), where n is the length of strs, and m is the maximum length of a string in strs.
// (REMEMBER m! Important to remember the non-negligible dependency on the max length m! Here m is at most 100)

// Space Complexity: O(n*m), the total information content stored in the solution.

// O(m + 26) in time
string GetSignature(const string& s) {
    vector<int> letter_occurencies(26);
    string signature;

    for (char c : s) {
        ++letter_occurencies[c-'a']; // ASCII
    }

    for (int i  = 0; i < 26; ++i) {
        if (letter_occurencies[i] > 0) {
            signature.push_back('a'+i);
            signature.append(to_string(letter_occurencies[i])); // 'append' complexity seems to be unspecified (can be linear in the new size of str)
        }
    }

    return signature;
}

// time: O(n*m + n*26), space: O(n*m) / better than 50% of the submissions in time and 15% in space
vector<vector<string>> GroupAnagrams(const vector<string>& strs) {
    vector<vector<string>> solution;
    unordered_map<string, vector<string>> anagrams;

    for (string s : strs) {
        string signature = GetSignature(s);
        // if (anagrams.find(signature) == anagrams.end()) {
        //     anagrams[signature] = vector<string>();
        // }
        anagrams[signature].push_back(s);
    }

    for (const auto& [_, anagrams_with_same_signature] : anagrams) {
        solution.push_back(anagrams_with_same_signature);
    }

    return solution;
}

// time: O(n * m log m), space: n * m / better than 80% of the submissions in time and 75% in space (because m is at most 100 here)
vector<vector<string>> GroupAnagramsSort(vector<string>& strs) {
    vector<vector<string>> solution;
    unordered_map<string, vector<string>> anagrams;

    for (string s : strs) { // n
        string w = s; // m

        sort(w.begin(), w.end()); // w signature is the sorted string s -> m log m time complexity
        anagrams[w].push_back(s);
    }

    for (const auto& [_, anagrams_with_same_signature] : anagrams) { // O(n)
        solution.push_back(anagrams_with_same_signature);
    }

    return solution;
}

int main() {
    // Input: strs = ["eat","tea","tan","ate","nat","bat"]
    // Expected Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> ans = GroupAnagrams(strs);

    for (const vector<string>& anagrams_with_same_signature : ans) {
        for (const string& s : anagrams_with_same_signature ) {
            cout << s << " ";
        }
        cout << '/' << endl;
    }

    // Just for fun to remember the syntax of a lambda function:
    /*
    function<void(const string&)> PrintElement = [](const string& s) -> void {cout << s << ", ";};
    for(const vector<string>& anagrams_with_same_signature : ans) {
        PrintVector(anagrams_with_same_signature, PrintElement); // from my #include "tools.cpp"
    }
    for (string el : {"roger", "neuma", "renner", "norma"}) {
        PrintElement(el);
    }
    */

    return 0;
}
