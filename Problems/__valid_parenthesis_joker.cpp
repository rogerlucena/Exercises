#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://leetcode.com/problems/valid-parenthesis-string/
// interesting: think about using an additional stack for the 'jokers', always using indexes
// or think about dp with intervals, or see the great trick about the possible final 'balance' interval (below)

// Given a string containing only three types of characters: '(', ')' and '*', write a function 
// to check whether this string is valid. We define the validity of a string by these rules:

// Any left parenthesis '(' must have a corresponding right parenthesis ')'.
// Any right parenthesis ')' must have a corresponding left parenthesis '('.
// Left parenthesis '(' must go before the corresponding right parenthesis ')'.
// '*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
// An empty string is also valid.

// Example:
// Input: "(*))"
// Output: True

bool checkValidString(string s) {
	stack<int> open;
	stack<int> joker;

	for(int i = 0; i < s.size(); ++i) {
		char c = s[i];
		if(c == '(') {
			open.push(i);
		} else if(c == '*') {
			joker.push(i);
		} else {
			if(!open.empty()) {
				open.pop();
			} else if(!joker.empty()) {
				joker.pop();
			} else {
				return false;
			}
		}
	}

	while (!open.empty()) {
		int openPos = open.top();
		open.pop();
		if(!joker.empty() && openPos < joker.top()) {
			joker.pop();
		} else {
			return false;
		}
	}

	return true;
}

// Website solution (greedy)
// Great trick: track only the possible final interval "balance" (number of opened left brackets) [lo, hi] =D
// For example: if we have string '(***)', then as we parse each symbol, the set of possible values for the 
// balance is [1] for '('; [0, 1, 2] for '(*'; [0, 1, 2, 3] for '(**'; [0, 1, 2, 3, 4] for '(***', 
// and [0, 1, 2, 3] for '(***)'.
bool checkValidStringWebsite(string s) {
	int lo = 0, hi = 0;
	for (char c : s) {
		lo += c == '(' ? 1 : -1;
		hi += c != ')' ? 1 : -1;
		if (hi < 0) {
			break;
		}

		lo = max(lo, 0);
	}

	return lo == 0; // check if possible to reach 0 opened left brackets by the end
}

int main() {
	string s = "(*()"; // ans: true

	cout << "Answer: " << checkValidString(s) << endl;
	return 0;
}