#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://leetcode.com/problems/longest-valid-parentheses/
// Remember: use a stack with the indexes (great hint for parentheses problems, remember that).

// Given a string containing just the characters '(' and ')', find the length of the longest 
// valid (well-formed) parentheses substring.

// Example 1:
// Input: "(()"
// Output: 2
// Explanation: The longest valid parentheses substring is "()"

// Example 2:
// Input: ")()())"
// Output: 4
// Explanation: The longest valid parentheses substring is "()()"

int longestValidParentheses(string s) {
    int longest = 0;
	vector<int> lastSizeFinishing(s.size(), 0);
	stack<int> st;
	for(int i = 0; i < s.size(); ++i) {
		if(s[i] == '(') {
			st.push(i);
		} else {
			if(!st.empty()) {
				int start = st.top();
				st.pop();
				int lastSize = start > 0 ? lastSizeFinishing[start-1] : 0;
				lastSizeFinishing[i] = lastSize + (i-start+1);
				longest = max(longest, lastSizeFinishing[i]);
			}
		}
	}

	return longest;
}

// ---
// Solution with Dynamic Programming
int longestValidParenthesesDP(string s) {
	vector<int> lastSizeFinishingAt(s.size(), 0);
	int longest = 0;
	for(int i = 1; i < s.size(); ++i) {
		if(s[i] == ')') {
			if(s[i-1] == '(') {
				int previousSize = i-2 >= 0 ? lastSizeFinishingAt[i-2] : 0;
				lastSizeFinishingAt[i] = previousSize + 2;
			} else if(i-1-lastSizeFinishingAt[i-1] >= 0){
				int start = i-1-lastSizeFinishingAt[i-1];
				if(s[start] == '(') {
					int previousSize = start-1 >= 0 ? lastSizeFinishingAt[start-1] : 0;
					lastSizeFinishingAt[i] = previousSize + (i-start+1);
				}
			}

			longest = max(longest, lastSizeFinishingAt[i]);
		} 
	}

	return longest;
}

// ---
// Time complexity exceeded below:
void updateLongest(const string &s, int start, int &longest) {
	stack<char> st;
	int j = start;
	for(; j < s.size(); ++j) {
		if(s[j] == '(') {
			st.push('(');
		} else {
			if(st.empty()) {
				break;
			}
			st.pop();
		}

		if(st.empty()) {
			longest = max(longest, j - start + 1);
		}
	}
}

int longestValidParenthesesOld(string s) {
    int longest = 0;
	for(int i = 0; i < s.size(); ++i) {
		updateLongest(s, i, longest);
	}

	return longest;
}

int main() {
	// string s = "(()"; // ans: 2
	// string s = ")()())"; // ans: 4
	string s = "()(())"; // ans: 6
	cout << "Answer: " << longestValidParentheses(s) << endl;

	return 0;
}