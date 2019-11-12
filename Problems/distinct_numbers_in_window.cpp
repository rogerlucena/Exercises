#include <iostream>
#include <vector>
#include <unordered_map>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/distinct-numbers-in-window/

// You are given an array of N integers, A1, A2 ,…, AN and an integer K. Return the of count of distinct numbers in all windows of size K.

// Formally, return an array of size N-K+1 where i’th element in this array contains number of distinct elements in sequence Ai, Ai+1 ,…, Ai+k-1.

// Note:
//  If K > N, return empty array.
//  A[i] is a signed integer

// For example,
// A = [1, 2, 1, 3, 4, 3] and K = 3
// All windows of size K are:
// [1, 2, 1]
// [2, 1, 3]
// [1, 3, 4]
// [3, 4, 3]
// So, we return an array [2, 3, 3, 2].

vector<int> dNums(vector<int> &A, int B) {
	vector<int> ans;
	if(B > A.size() || A.size() == 0 || B <= 0) {
		return ans;
	}

	unordered_map<int, int> m;
	int i=0;
	for(; i < B; ++i) {
		if(m.find(A[i]) != m.end()) {
			m[A[i]] += 1;
		} else {
			m[A[i]] = 1;
		}
	}
	ans.push_back(m.size());

	for(; i < A.size(); ++i) {
		int exitIndex = i-B;
		if(m[A[exitIndex]] > 1) {
			m[A[exitIndex]] -= 1;
		} else {
			m.erase(A[exitIndex]);
		}

		if(m.find(A[i]) != m.end()) {
			m[A[i]] += 1;
		} else {
			m[A[i]] = 1;
		}

		ans.push_back(m.size());
	}
	
	return ans;
}


int main() {
	vector<int> A = {1, 2, 1, 3, 4, 3};
	int B = 3;
	printVector(dNums(A, B));

	return 0;
}