#include <iostream>
#include <vector>
#include <string>

using namespace std;

// https://leetcode.com/problems/decode-string/

// Given an encoded string, return its decoded string.
// The encoding rule is: k[encoded_string], where the encoded_string inside the square 
// brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
// You may assume that the input string is always valid; No extra white spaces, square brackets 
// are well-formed, etc.
// Furthermore, you may assume that the original data does not contain any digits and that digits are only for 
// those repeat numbers, k. For example, there won't be input like 3a or 2[4].

// Example 1:
// Input: s = "3[a]2[bc]"
// Output: "aaabcbc"

// Example 2:
// Input: s = "3[a2[c]]"
// Output: "accaccacc"

// Recursion, reference to an index
bool isDigit(char c) {
	return '0' <= c && c <= '9'; 
}

int extractNumber(const string &s, int &i) {
	int n = 0;
	for(; isDigit(s[i]); ++i) {
		n *= 10;
		n += s[i] - '0';
	}
	return n;
}

string decodeStringUtil(const string &s, int &i) {
	string ans = "";
	for(; i < s.size(); ++i) {
		if(s[i] == ']') {
			break;
		}

		if(isDigit(s[i])) {
			int rep = extractNumber(s, i);
			++i; // skip '['
			string toAppend = decodeStringUtil(s, i);
			for(int r = 1; r <= rep; ++r) {
				ans.append(toAppend);
			}
			continue;
		}

		ans.push_back(s[i]); // only a single letter, push it to the back of ans
	}

	return ans;
}

string decodeString(string s) {
	int i = 0;
	return decodeStringUtil(s, i);
}

int main() {
	string s = "3[a]2[bc]";
	cout << decodeString(s) << endl; // "aaabcbc"

	s = "3[a2[c]]";
	cout << decodeString(s) << endl; // "accaccacc"

	return 0;
}