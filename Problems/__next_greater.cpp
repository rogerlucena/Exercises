#include <iostream>
#include <vector>
#include <stack>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/nextgreater/
// Idea: use stack to do it in-place

// Given an array, find the next greater element G[i] for every element A[i] in the array. The Next greater Element for an 
// element A[i] is the first greater element on the right side of A[i] in array.
// More formally,

// G[i] for an element A[i] = an element A[j] such that 
//     j is minimum possible AND 
//     j > i AND
//     A[j] > A[i]
// Elements for which no greater element exist, consider next greater element as -1.

// Example:
// Input : A : [4, 5, 2, 10]
// Output : [5, 10, 10, -1]

// Example 2)
// Input : A : [3, 2, 1]
// Output : [-1, -1, -1]

vector<int> nextGreater(vector<int> &A) {
	int size = A.size();
	if(size == 0) {
		return A;
	}

	stack<int> s;
	s.push(0);

	for(int i = 1; i < size; ++i) {
		int next = A[i];
		while(!s.empty() && next > A[s.top()]) {
			A[s.top()] = next;
			s.pop();
		}
		s.push(i);
	}

	while(!s.empty()) {
		A[s.top()] = -1;
		s.pop();
	}

	return A;
}

int main() {
	vector<int> A = {4, 5, 2, 10};
	// vector<int> A = {3, 2, 1};

	cout << "Answer:" << endl;
	printVector(nextGreater(A));

	return 0;
}