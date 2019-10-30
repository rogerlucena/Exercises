#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/remove-duplicates-from-sorted-array/

// Remove duplicates from Sorted Array, in place, and return the new length

int removeDuplicates(vector<int> &A) {
	if(A.size() == 0) {
		return 0;
	}

	int initialSize = A.size();
	int i1 = 0;
	for(int i2 = 1; i2 < initialSize; ++i2) {
		if(A[i2] == A[i1]) {
			continue;
		}
		A[++i1] = A[i2];
	}

	for(int i = i1 + 1; i < initialSize; ++i) {
		A.pop_back();
	}

	assert(i1+1 == A.size());

	return i1 + 1;
}

int main() {
	vector<int> A = {1, 1, 2, 3, 4, 4, 4, 5};
	cout << "Answer: " << removeDuplicates(A) << endl;
	printVector(A);

	return 0;
}