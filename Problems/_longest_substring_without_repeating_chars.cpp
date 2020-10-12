#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/longest-substring-without-repeating-characters/

// Given a string s, find the length of the longest substring without repeating characters.

// Example:
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3.

// Time complexity : O(n)O(n). Index jj will iterate nn times.
// Space complexity : O(min(m, n))O(min(m,n)). Same as the previous approach. We need O(k) space for the sliding 
// window, where k is the size of the Set. The size of the Set is upper bounded by the size of the string n and the 
// size of the charset/alphabet m.
int lengthOfLongestSubstring(string s) {
	unordered_map<char, int> found;
	int maxLength = 0;
	for(int i = 0, j = 0; j < s.size(); ++j) {
		if(found.find(s[j]) != found.end()) {
			i = max(found[s[j]] + 1, i);
		}

		maxLength = max(maxLength, j-i+1);
		found[s[j]] = j; // if s[j] already found before, previous value not relevant anymore since it is "< i"
	}

	return maxLength;
}

int lengthOfLongestSubstringMine(string s) {
	unordered_map<char, int> found;
	int maxLength = 0;
	for(int i = 0, j = 0; i < s.size();) {
		while(j < s.size() && (found.find(s[j]) == found.end() || found[s[j]] < i)) {
			found[s[j]] = j;
			maxLength = max(maxLength, j-i+1);
			++j;
		}

		if(j == s.size()) {
			return maxLength;
		}

		i = found[s[j]] + 1;
	}

	return maxLength;
}

int main() {
	cout << "Hello, World!";
	return 0;
}