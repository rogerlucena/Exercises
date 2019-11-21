#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/palindrome-partitioning-ii/

// Given a string A, partition A such that every substring of the partition is a palindrome.
// Return the minimum cuts needed for a palindrome partitioning of A.

// Constraints:
// 1 <= length(A) <= 501

// Examples
// Input 1:
//     A = "aba"
// Output 1:
//     0
// Explanation 1:
//     "aba" is already a palindrome, so no cuts are needed.

// Input 2:
//     A = "aab" 
// Output 2:
//     1
// Explanation 2:
//     Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.

// Analyzing str[s, e]
bool isPalindrome(string &str, int s, int e) {
	int mid = (s + e) / 2;
	for(int i = 0; i <= mid-s ; ++i) {
		if(str[s+i] != str[e-i]) {
			return false;
		}
	}

	return true;
}

int minCutHelper(string &A, int pos, vector<int> &memo) {
	if(pos == A.size()-1) {
		return 0;
	}

	if(memo[pos] != -1) {
		return memo[pos];
	}

	int ans = INT_MAX;
	if(isPalindrome(A, pos, A.size()-1)) {
		ans = 0;
	} else {
		for(int i = pos + 1; i < A.size(); ++i) {
			ans = isPalindrome(A, pos, i-1) ? min(ans, 1 + minCutHelper(A, i, memo)) : ans;
		}
	}
	memo[pos] = ans;

	return memo[pos];
}

int minCut(string A) {
	if(A.size() < 2) {
		return 0;
	}

	vector<int> memo(A.size()-1, -1);

	return minCutHelper(A, 0, memo);
}


int main() {
	// string A = "aba"; // ans: 0
	string A = "aab"; // ans: 1
	cout << "Answer: " << minCut(A) << endl;

	return 0;
}