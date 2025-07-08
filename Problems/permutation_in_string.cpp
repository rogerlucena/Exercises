#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/permutation-string
// https://leetcode.com/problems/permutation-in-string
// Review: to compare the char count of two strings use 26-vector if lowercase English letters
// for eg (here), or sort the strings, or use hash map for char count.
// Obs: possible to compare content of two vectors just using == (compares size and values), for 
// hash maps too (checks size and all key-value pairs, order not importante here).

// Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
// In other words, return true if one of s1's permutations is the substring of s2.

// Example 1:
// Input: s1 = "ab", s2 = "eidbaooo"
// Output: true
// Explanation: s2 contains one permutation of s1 ("ba").

// Example 2:
// Input: s1 = "ab", s2 = "eidboaoo"
// Output: false
 
// Constraints:
// 1 <= s1.length, s2.length <= 104
// s1 and s2 consist of lowercase English letters.

bool isSameCount(const vector<int>& c1, const vector<int>& c2) {
    if (c1.size() != c2.size()) {
        return false;
    }

    for (int i = 0; i < c1.size(); ++i) {
		if (c1[i] != c2[i]) {
			return false;
		}
	}

	return true;
}

bool checkInclusion(string s1, string s2) {
	if (s1.size() > s2.size()) {
		return false;
	}
	
	vector<int> count1(26, 0);
	vector<int> count2(26, 0);

	for (int i = 0; i < s1.size(); ++i) {
		++count1[s1[i] - 'a'];
		++count2[s2[i] - 'a'];
	}

    for (int l = 0, r = s1.size() - 1; r < s2.size(); ++l, ++r) {
		if (isSameCount(count1, count2)) { // can compare content just using ==, for hash maps too.
			return true;
		}

		--count2[s2[l] - 'a'];
        if (r + 1 < s2.size()) ++count2[s2[r + 1] - 'a'];
    }

	return false;
}

int main() {
	cout << "Hello, World!";
	return 0;
}