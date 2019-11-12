#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/gray-code/

// The gray code is a binary numeral system where two successive values differ in only one bit.

// Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. 
// A gray code sequence must begin with 0.

// For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
// 00 - 0
// 01 - 1
// 11 - 3
// 10 - 2

// There might be multiple gray code sequences possible for a given n.
// Return any such sequence.

void grayCodeHelper(int A, vector<int> &ans) {
	if(A == 0) {
		return;
	} else if(A == 1) {
		ans = {0, 1};
		return;
	}

	grayCodeHelper(A-1, ans);
	int size = ans.size();
	for(int i = size-1; i >= 0; --i) {
		ans.push_back(ans[i] | 1 << (A-1));
	}
}

vector<int> grayCode(int A) {
	vector<int> ans;
    grayCodeHelper(A, ans);

	return ans;
}

int main() {
	int A = 2;
	printVector(grayCode(A));

	return 0;
}