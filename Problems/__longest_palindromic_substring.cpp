#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/longest-palindromic-substring
// https://leetcode.com/problems/longest-palindromic-substring
// Remember: for palindrome, it is useful to think about the center of the palindrome and then try to expand on
// each side (separating the odd and the even case).
// Obs: could have used a 2D DP here too (worse in space) - memo[i][j] holding true if that substr already calculated before is a palindrome (if iterative bottom-up start i from n-1 -> 0 and j >= i to have memo already filled).

// Given a string s, return the longest substring of s that is a palindrome.
// If there are multiple palindromic substrings that have the same length, return any one of them.

// Example 1:
// Input: s = "ababd"
// Output: "bab"
// Explanation: Both "aba" and "bab" are valid answers.

// Example 2:
// Input: s = "abbc"
// Output: "bb"

// Constraints:
// 1 <= s.length <= 1000

// O(n^2) in time and O(1) in extra space (other than the output string).
// (better than O(n^3) of the brute-force = for every possible substr i,j check in O(n) if it is palindrome)
string longestPalindrome(string s) {
	int max_size = 0;
	int start = 0;

	for (int i = 0; i < s.size(); ++i) {
		// Odd length.
		int l = i;
		int r = i;
		while (l >= 0 && r < s.size() && s[l] == s[r]) {
			if (r - l + 1 > max_size) {
				start = l;
				max_size = r - l + 1;
			}
			--l;
			++r;
		}

		// Even length.
		l = i;
		r = i + 1;
		while (l >= 0 && r < s.size() && s[l] == s[r]) {
			if (r - l + 1 > max_size) {
				start = l;
				max_size = r - l + 1;
			}
			--l;
			++r;
		}
	}

	return s.substr(start, max_size);
}

int main() {
	cout << "Hello, World!";
	return 0;
}