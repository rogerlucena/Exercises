#include <iostream>
#include <vector>
#include <string>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/palindrome-partitioning/

// Given a string s, partition s such that every string of the partition is a palindrome.
// Return all possible palindrome partitioning of s.

// For example, given s = "aab",
// Return
//   [
//     ["a","a","b"]
//     ["aa","b"],
//   ]

// Ordering the results in the answer : Entry i will come before Entry j if :
// len(Entryi[0]) < len(Entryj[0]) OR
// (len(Entryi[0]) == len(Entryj[0]) AND len(Entryi[1]) < len(Entryj[1])) OR
// ...
// (len(Entryi[0]) == len(Entryj[0]) AND … len(Entryi[k] < len(Entryj[k]))

bool isPalindrome(string &str, int s, int e) {
	while (s < e) {
		if (str[s] != str[e]){
			return false;
		}
		s++;
		e--;
	}

	return true;
}

// Website solution
void partitionHelper(int i, vector<string> &current, string &s, vector<vector<string>> &ans) {
	if (i == s.length()) {
		// We reached the end of the string.
		// Valid sequence of strings found.
		ans.push_back(current);
		return;
	}

	for (int j = i; j < s.length(); ++j) {
		if (isPalindrome(s, i, j)) {
			current.push_back(s.substr(i, j - i + 1));
			partitionHelper(j + 1, current, s, ans);
			current.pop_back();
		}
	}
}

vector<vector<string>> partition(string A) {
	vector<vector<string> > ans;
	vector<string> current;
	partitionHelper(0, current, A, ans);

	return ans;
}

int main() {
	string A = "aab";
	function<void(const string&)> printString = [](const string &s) -> void {cout << s;};
	for(vector<string> p : partition(A)) {
		printVector(p, printString);
	}

	return 0;
}