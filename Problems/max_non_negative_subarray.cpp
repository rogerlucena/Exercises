#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/max-non-negative-subarray/

// Given an array of integers, A of length N, find out the maximum sum sub-array of non negative numbers from A.
// The sub-array should be contiguous
// 		1. If there is a tie, then compare with segment's length and return segment which has maximum length.
// 		2. If there is still a tie, then return the segment with minimum starting index.

vector<int> maxset(vector<int> &A) {
	long maxSum = LONG_MIN;
	long currSum = 0;
	int iMax = -1, jMax = -1, iCurr = 0, jCurr = 0;

	for(int i = 0; i < A.size(); ++i) {
		if(A[i] < 0) {
			iCurr = jCurr = i+1;
			currSum = 0;
			continue;
		}

		currSum += A[i];
		jCurr = i;

		if(currSum > maxSum || (currSum == maxSum && (jCurr-iCurr > jMax-iMax))) {
			maxSum = currSum;
			iMax = iCurr;
			jMax = jCurr;
		}
	}

	vector<int> ans;
	ans.reserve(jMax-iMax+1);
	if(iMax > -1) {
		for(int i = iMax; i <= jMax; ++i) {
			ans.push_back(A[i]);
		}
	}

	return ans;
}


int main() {
	vector<int> A = {1, 2, 5, -7, 2, 3};
	// vector<int> A = {10, -1, 2, 3, -4, 100};
	// vector<int> A = {0, 0, -1, 0};

	vector<int> ans = maxset(A);
	cout << "Answer:" << endl;
	printVector(ans);

	return 0;
}