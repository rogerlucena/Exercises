#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/single-number-ii/

// Given an array of integers, every element appears thrice except for one which occurs once.
// Find that element which does not appear thrice.
// Note: Your algorithm should have a linear runtime complexity.
// Could you implement it without using extra memory?

// Doing XOR with everyone does not work -> only if numbers repeating a pair number of times, here 3 is odd!
// Trick: analyse every bit modulos 3 and use "|=" and "<<" to contruct the answer
int singleNumber(const vector<int> &A) {
	int ans = 0;
	vector<int> bitCount(32, 0);

	for(int i = 0; i < 32; ++i) {
		for(int el : A) {
			if(((el >> i) & 1) == 1) {
				++bitCount[i];
			} 
		}
		bitCount[i] %= 3;
		ans |= (bitCount[i] << i);
	}

	return ans;
}

int main() {
	vector<int> A = {1, 2, 4, 3, 3, 2, 2, 3, 1, 1};
	cout << "Answer: " << singleNumber(A) << endl;
	return 0;
}