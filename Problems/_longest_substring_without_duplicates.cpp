#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// https://neetcode.io/problems/longest-substring-without-duplicates
// https://leetcode.com/problems/longest-substring-without-repeating-characters
// Review: nice to use a hash map 'found[c]' to store the last index on which char 'c' was found.
// Sliding window valid because the others will be of smaller length and then can increase "start".

// Given a string s, find the length of the longest substring without duplicate characters.

// Example 1:
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3.

// Example 2:
// Input: s = "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.

// Constraints:
// 0 <= s.length <= 5 * 104
// s consists of English letters, digits, symbols and spaces.

// Optimal (but same time and space complexity as below):
// For each char in s verify if it can be the rightmost index of the longest substring, eliminating the other possibilities.
int lengthOfLongestSubstring(string s) {
	unordered_map<char, int> found;
	int longest = 0;

	int l = 0, r = 0;
	while (r < s.size()) {
		if (found.count(s[r])) {
			l = max(l, found[s[r]] + 1);
		}

		longest = max(longest, r - l + 1);
		found[s[r]] = r;
		++r;
	}

	return longest;
}

// Time O(N), Space O(M)
// N is the length of the string and 
// M is the total number of unique characters in the string.
int lengthOfLongestSubstring(string s) {
    unordered_set<char> char_set;
    int start = 0;
    int longest = 0;

    for (int i = 0; i < s.size(); ++i) {
        while (char_set.count(s[i])) {
            char_set.erase(s[start]);
            ++start;
        }
        char_set.insert(s[i]);
        longest = max(longest, i - start + 1);
    }

    return longest;
}

// Other file - older:
// Time complexity : O(n). Index j will iterate n times.
// Space complexity : O(min(m, n)). Same as the previous approach. We need O(k) space for the sliding 
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
		found[s[j]] = j; 
	}

	return maxLength;
}

int main() {
	cout << "Hello, World!";
	return 0;
}