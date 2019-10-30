#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/longest-common-prefix/

// Given the array of strings A, you need to find the longest string S 
// which is the prefix of ALL the strings in the array.

bool charPresentAtPositionForAll(char c, int pos, const vector<string> &A) {
	for(string s : A) {
		if(s[pos] != c) {
			return false;
		}
	}
	return true;
}

string longestCommonPrefix(vector<string> &A) {
	if(A.size() == 0) {
		return "";
	} 
	if(A.size() == 1) {
		return A[0];
	}

	int indexOfSmaller = 0;
	string ans = "";
	for(int i = 1; i < A.size(); ++i) {
		indexOfSmaller = A[i].size() < A[indexOfSmaller].size() ? i : indexOfSmaller;
	}

	for(int j = 0; j < A[indexOfSmaller].size(); ++j) {
		char c = A[indexOfSmaller][j];
		if(charPresentAtPositionForAll(c, j, A)) {
			ans.push_back(c);
		} else {
			break;
		}
	}

	return ans;
}

int main() {
	vector<string> A = {"abcdefgh", "abcefgh"};
	// vector<string> A = {"abcdefgh", "aefghijk", "abcefgh"};
	// vector<string> A = {"abab", "ab", "abcd"};
	cout << "Answer: " << longestCommonPrefix(A) << endl;

	return 0;
}