#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://leetcode.com/problems/valid-parentheses/

// Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
// An input string is valid if:
// Open brackets must be closed by the same type of brackets.
// Open brackets must be closed in the correct order.
 
// Example 1:
// Input: s = "()"
// Output: true
// Example 2:
// Input: s = "()[]{}"
// Output: true

char getOpenFor(char c) {
	switch(c) {
		case ')':
			return '(';
		case ']':
			return '[';
		case '}':
			return '{';
		default:
			return 'a';
	}
}

bool isValid(string s) {
	stack<char> open;
	for (char c : s) {
		// cout << "open size: " << open.size() << endl;
		switch (c) {
		case '(': case '[': case '{':
			open.push(c);
			break;
		default:
			if (open.empty() || open.top() != getOpenFor(c)) {
				return false;
			}
			open.pop();
			break;
		}
	}

	return open.empty();
}

int main() {
	string s = "()";
	cout << "Answer: " << isValid(s) << endl;
	
	return 0;
}