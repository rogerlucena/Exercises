#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/longest-repeating-substring-with-replacement (solution: https://youtu.be/gqXU1UyA8pk?si=KZ8LgS75kLP-tuj2)
// https://leetcode.com/problems/longest-repeating-character-replacement
// Review: sliding window of changing size if for that left index increasing the right index will keep the window 
// invalid - and then can eliminate/skip those possibilities by increasing the left index. Also, [left+1, right] will 
// have <= length than the previous valid [left, right-1] (we are looking for max length window here), so for left+1 start checking [left+1, right] onwards.
// "valid" window here is (length - max_char_count) <= k (min number of changes needed <= k), if for [left, right] is invalid
// then increasing the right index will keep the window invalid (length receives +1 and max_char_count either +1 or +0), thus 
// can discard all those other windows starting in left and can do ++left. Note that the other smaller lengths starting in 
// left+1 will also be <= the previous valid window found, thus can start checking from [left+1, right] onwards, increasing 'right' after if valid.

// You are given a string s consisting of only uppercase english characters and an integer k. You can choose up to k characters 
// of the string and replace them with any other uppercase English character.
// After performing at most k replacements, return the length of the longest substring which contains only one distinct character.

// Example 1:
// Input: s = "XYYX", k = 2
// Output: 4
// Explanation: Either replace the 'X's with 'Y's, or replace the 'Y's with 'X's.

// Example 2:
// Input: s = "AAABABB", k = 1
// Output: 5

// Constraints:
// 1 <= s.length <= 1000
// 0 <= k <= s.length

// O(N) in time and O(26) in space.
int characterReplacement(string s, int k) {
    vector<int> char_count(26, 0);
	int longest = 0;
	for (int l = 0, r = 0; r < s.size();) {
		++char_count[s[r] - 'A'];
		while ((r - l + 1) - *max_element(char_count.begin(), char_count.end()) > k) { // to have a "valid" substring.
			--char_count[s[l] - 'A'];
			++l;
		}
		longest = max(longest, r - l + 1);
		++r;
	}

	return longest;
}

int main() {
	cout << "Hello, World!";
	return 0;
}