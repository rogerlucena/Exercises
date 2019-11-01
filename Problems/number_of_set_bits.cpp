#include <iostream>

using namespace std;

// https://www.interviewbit.com/problems/number-of-1-bits/

// Write a function that takes an unsigned integer and returns the number of 1 bits it has.

int numSetBits(unsigned int A) {
	int count = 0;
	while(A != 0) {
		++count;
		A = A & (A-1); // will clear the lowest set bit of x
	}

	return count;
}

int main() {
	unsigned int A = 11;
	cout << "Answer: " << numSetBits(A);
	return 0;
}