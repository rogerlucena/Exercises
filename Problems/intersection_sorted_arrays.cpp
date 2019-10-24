#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/intersection-of-sorted-arrays/

// Given 2 sorted arrays, find all the elements which occur in both the arrays.
// Ex:
// Input : 
//     A : [1 2 3 3 4 5 6]
//     B : [3 3 5]

// Output : [3 3 5]

vector<int> intersect(const vector<int> &A, const vector<int> &B) {
	vector<int> ans;
	int i1 = 0;
	int i2 = 0;
	while (i1 < A.size() && i2 < B.size()) {
		if(A[i1] < B[i2]) {
			++i1;
		} else if(A[i1] > B[i2]) {
			++i2;
		} else {
			ans.push_back(A[i1]);
			++i1;
			++i2;
		}
	}
	
	return ans;
}


int main() {
	vector<int> A = {1, 2, 3, 3, 4, 5, 6};
	vector<int> B = {3, 3, 5};
	cout << "Answer: " << endl;
	printVector(intersect(A, B));
	return 0;
}