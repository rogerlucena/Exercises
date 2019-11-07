#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://www.interviewbit.com/problems/diffk-ii/

// Given an array A of integers and another non negative integer k, find if there exists 2 indices i 
// and j such that A[i] - A[j] = k, i != j.

// Example :
// Input :
// A : [1 5 3]
// k : 2
// Output :
// 1

int iffPossible(const vector<int> &A, int B) {
	unordered_map<int, int> m = {};
	for(int i = 0; i < A.size(); ++i) {
		m[A[i]] = i;
	}

	for(int i = 0; i < A.size(); ++i) {
		int required = A[i] - B;
		auto got = m.find(required);
		if(got != m.end() && got->second != i) { // remember: they must have different indexes
			return 1;
		}
	}

	return 0;
}


int main() {
	vector<int> A = {1, 5, 3};
	int B = 2;

	cout << "Answer: " << iffPossible(A, B) << endl;
	
	return 0;
}