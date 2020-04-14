#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/explore/other/card/30-day-leetcoding-challenge/529/week-2/3299/
// Interesting: perform a modulus operation with negative numbers -> (a % b + b) % b 

// You are given a string s containing lowercase English letters, and a matrix shift, where 
// shift[i] = [direction, amount]:

// direction can be 0 (for left shift) or 1 (for right shift). 
// amount is the amount by which string s is to be shifted.
// A left shift by 1 means remove the first character of s and append it to the end.
// Similarly, a right shift by 1 means remove the last character of s and add it to the beginning.
// Return the final string after all operations.

// Example 1:

// Input: s = "abc", shift = [[0,1],[1,2]]
// Output: "cab"
// Explanation: 
// [0,1] means shift to left by 1. "abc" -> "bca"
// [1,2] means shift to right by 2. "bca" -> "cab"

string stringShift(string s, vector<vector<int>> &shift) {
    int shiftValue = 0;
	for(vector<int> p : shift) {
		shiftValue += (p[0] == 0 ? -1 : 1) * p[1];
	}

	int len = s.size();
	int rightShift = (shiftValue % len + len) % len;
	string ans = s.substr(len - rightShift, rightShift);
	ans.append(s.substr(0, len - rightShift));

	return ans;
}

int main() {
	// vector<vector<int>> shift = {{0,1}, {1,2}};
	// string s = "abc"; // ans: "cab"

	// vector<vector<int>> shift = {{1,1}, {1,1}, {0,2}, {1,3}};
	// string s = "abcdefg"; // ans: "efgabcd"

	vector<vector<int>> shift = {{0,7}, {1,7}, {1,0}, {1,3}, {0,3}, {0,6}, {1,2}};
	string s = "wpdhhcj"; // ans: "hcjwpdh"

	cout << "Answer: " << stringShift(s, shift) << endl;
	return 0;
}