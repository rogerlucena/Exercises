#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// https://neetcode.io/problems/longest-substring-without-duplicates
// https://leetcode.com/problems/longest-substring-without-repeating-characters
// Quick: sliding window valid because the others will be of smaller length and then can increase "start".

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

// Optimal below from Neetcode solutions (but same time and space complexity as above):
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> mp;
    int l = 0, res = 0;

    for (int r = 0; r < s.size(); r++) {
        if (mp.find(s[r]) != mp.end()) {
            l = max(mp[s[r]] + 1, l);
        }
        mp[s[r]] = r; // record the last time that char was found.
        res = max(res, r - l + 1);
    }
    return res;
}

int main() {
	cout << "Hello, World!";
	return 0;
}