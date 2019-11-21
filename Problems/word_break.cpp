#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// https://www.interviewbit.com/problems/word-break/

// Given a string A and a dictionary of words B, determine if A can 
// be segmented into a space-separated sequence of one or more dictionary words.

// Constraints:
// 1 <= len(A) <= 6500
// 1 <= len(B) <= 10000
// 1 <= len(B[i]) <= 20

// Examples:
// Input 1:
//     A = "myinterviewtrainer",
//     B = ["trainer", "my", "interview"]
// Output 1:
//     1
// Explanation 1:
//     Return 1 ( corresponding to true ) because "myinterviewtrainer" can be segmented as "my interview trainer".  

// Input 2:
//     A = "a"
//     B = ["aaa"]
// Output 2:
//     0
// Explanation 2:
//     Return 0 ( corresponding to false ) because "a" cannot be segmented as "aaa".

int wordBreakHelper(const string &A, int pos, const unordered_set<string> &bWordsInA, vector<int> &memo) {
	if(pos == A.size()) {
		return 1;
	}

	if(memo[pos] != -1) {
		return memo[pos];
	}

	int ans = 0;
	int size = 1;
	while(!ans && pos+size <= A.size()) {
		string substr = A.substr(pos, size);
		if(bWordsInA.find(substr) != bWordsInA.end()) {
			ans = ans || wordBreakHelper(A, pos+size, bWordsInA, memo);
		}

		++size;
	}
	memo[pos] = ans;

	return memo[pos];
}

int wordBreak(string A, vector<string> &B) {
	if(A.empty()) {
		return 0;
	}

	unordered_set<string> bWordsInA;
	for(string w : B) {
		if(A.find(w) != string::npos) {
			bWordsInA.insert(w);
		}
	}

	vector<int> memo(A.size(), -1);

	return wordBreakHelper(A, 0, bWordsInA, memo);
}


int main() {
	string A = "myinterviewtrainer"; // ans: 1
    vector<string> B = {"trainer", "my", "interview"};

	// string A = "a"; // ans: 0
    // vector<string> B = {"aaa"};
	cout << "Answer: " << wordBreak(A, B) << endl;

	return 0;
}