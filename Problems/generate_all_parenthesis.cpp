#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

// https://www.interviewbit.com/problems/generate-all-parentheses-ii/

// Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses of length 2*n.

// For example, given n = 3, a solution set is:
// "((()))", "(()())", "(())()", "()(())", "()()()"

// Make sure the returned list of strings are sorted.

// Website solution
void generateHelper(string &current, int numOpenBrackets, int numClosedBrackets, int n, vector<string> &ans) {
	if (numOpenBrackets == numClosedBrackets && numOpenBrackets == n) {
		ans.push_back(current);
		return;
	}
	if (numOpenBrackets > n || numClosedBrackets > n) {
		// Invalid. 
		return;
	}

	// Now we have 2 options. We can either add '(' to the string or add ')' to the string. 
	// Option 1. Add '(' 
	if (numOpenBrackets < n) {
		current.push_back('(');
		generateHelper(current, numOpenBrackets + 1, numClosedBrackets, n, ans);
		current.pop_back();
	}
	// Option 2. Add ')'
	if (numClosedBrackets < numOpenBrackets) {
		current.push_back(')');
		generateHelper(current, numOpenBrackets, numClosedBrackets + 1, n, ans);
		current.pop_back();
	}
}

vector<string> generateParenthesis(int A) {
	vector<string> ans;
	string current = "";
	int numOpenBrackets = 0, numClosedBrackets = 0; 
	generateHelper(current, numOpenBrackets, numClosedBrackets, A, ans);

	return ans;
}


int main() {
	int A = 3;
	for(string s : generateParenthesis(A)) {
		cout << s << endl;
	}
	return 0;
}