#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/longest-common-prefix/
// // https://leetcode.com/problems/longest-common-prefix/submissions/

// Given the array of strings A, you need to find the longest string S 
// which is the prefix of ALL the strings in the array.

string longestCommonPrefix(vector<string> &A) {
	string ans = "";
	if(A.empty()) {
		return ans;
	}

	for(int i = 0; ; ++i) {
		if(i >= A[0].size()) {
			return ans;
		}

		char c = A[0][i];
		for(int j = 1; j < A.size(); ++j) {
			if(i >= A[j].size() || A[j][i] != c) {
				return ans;
			}
		}

		ans.push_back(c);
	}

	return ans;
}

int main() {
	vector<string> A = {"abcdefgh", "abcefgh"};
	// vector<string> A = {"abcdefgh", "aefghijk", "abcefgh"};
	// vector<string> A = {"abab", "ab", "abcd"};
	// vector<string> A = {"flower","flow","flight"}; // ans: "fl"
	cout << "Answer: " << longestCommonPrefix(A) << endl;

	return 0;
}