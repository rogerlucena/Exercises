#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://neetcode.io/problems/valid-parenthesis-string
// https://leetcode.com/problems/valid-parenthesis-string
// Remember: for parenthesis, consider using stack with indexes, where also include a stack for the "jokers" (stars).
// Or think about DP (variable "i" and "open" define the state), or with intervals - see the great trick about 
// the possible final 'balance' interval (below).

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

// Interesting: think about using an additional stack for the 'jokers' ('star'), always using indexes.
// O(N) in time and space.
bool checkValidString(string s) {
	stack<int> left;
	stack<int> star;

	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '(') {
			left.push(i);
		} else if (s[i] == '*') {
			star.push(i);
		} else { // ')'
			if (!left.empty()) {
				left.pop();
			} else if (!star.empty()) {
				star.pop();
			} else {
				return false;
			}
		}
	}

	while (!left.empty() && !star.empty()) {
		if (left.top() > star.top()) {
			return false;
		}
		left.pop();
		star.pop();
	}

	return left.empty();
}

// DP solution:
// O(N^2) in time and space.
bool dfs(const string& s, int i, int open, vector<vector<int>>& memo) {
    if (open < 0) {
        return false;
    }   
    if (i == s.size()) {
        return open == 0;
    }

    if (memo[i][open] != -1) {
        return memo[i][open];
    }

    bool res = false;
    if (s[i] == '(') {
        res = dfs(s, i + 1, open + 1, memo);
    } else if (s[i] == '*') {
        res = dfs(s, i + 1, open + 1, memo);
        res |= dfs(s, i + 1, open, memo);
        res |= dfs(s, i + 1, open - 1, memo);
    } else if (open > 0) { // ')'
        res = dfs(s, i + 1, open - 1, memo);
    }

    memo[i][open] = res;
    return res;
}

bool checkValidStringDP(string s) {
    vector<vector<int>> memo(s.size() + 1, vector<int>(s.size() + 1, -1));
    return dfs(s, 0, 0, memo);
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