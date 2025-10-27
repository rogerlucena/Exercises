#include <iostream>
// #include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/word-pattern
// Remember: how to tokeninze a string in C++ (space/tab/newline or customized separator below).

// Given a pattern and a string s, find if s follows the same pattern.

// Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s. Specifically:
// Each letter in pattern maps to exactly one unique word in s.
// Each unique word in s maps to exactly one letter in pattern.
// No two letters map to the same word, and no two words map to the same letter.
 
// Example 1:
// Input: pattern = "abba", s = "dog cat cat dog"
// Output: true
// Explanation:
// The bijection can be established as:
// 'a' maps to "dog".
// 'b' maps to "cat".

// Example 2:
// Input: pattern = "abba", s = "dog cat cat fish"
// Output: false

// Example 3:
// Input: pattern = "aaaa", s = "dog cat cat dog"
// Output: false

// Constraints:
// 1 <= pattern.length <= 300
// pattern contains only lower-case English letters.
// 1 <= s.length <= 3000
// s contains only lowercase English letters and spaces ' '.
// s does not contain any leading or trailing spaces.
// All the words in s are separated by a single space.

// Compatible even with C++11.
vector<string> splitBySpace(const string& str) {
	istringstream iss(str);
	vector<string> words;
	string token;
    while (iss >> token) {  // operator>> skips whitespaces/tabs/newlines automatically.
        words.push_back(token);
    }

    return words;
}

vector<string> splitByDelimiter(const string& s, const char delimiter) {
    istringstream iss(s);
    vector<string> words;
    string token;
    while (getline(iss, token, delimiter)) {
        if (!token.empty()) {  // skip empty tokens.
            words.push_back(token);
		}
    }

    return words;
}

// If you’re using C++20, this is the most modern and expressive approach.
// vector<string> splitBySpace(const string& str) {
//     vector<string> words;
//     for (auto&& token : views::split(str, ' ')) {  // from <ranges>.
//         string word(token.begin(), token.end());
//         if (!word.empty()) {  // skip empty tokens.
//             words.push_back(move(word));
// 		}
//     }

//     return words;
// }

bool wordPattern(string pattern, string s) {
	vector<string> words = splitBySpace(s);
	if (pattern.size() != words.size()) {
		return false;
	}

	unordered_map<char, string> m;
	unordered_set<string> seen;
	for (int i = 0; i < pattern.size(); ++i) {
		char p = pattern[i];
		string w = words[i];
		if (m.count(p)) {
			if (m[p] != w) {
				return false;
			}
		} else if(seen.count(w)) {
			return false;
		} else {
			m[p] = w;
			seen.insert(w);
		}
	}

	return true;
}

int main() {
	string input = "C++  is\na \tpowerful  language ";
    vector<string> words = splitBySpace(input);
    for (const string& w : words) {
		std::cout << w << endl;
	}
	cout << "-----" << endl;

	input = "C++  is a -**powerful -* language ";
    words = splitByDelimiter(input, '*');
    for (const string& w : words) {
		std::cout << w << endl;
	}

	return 0;
}