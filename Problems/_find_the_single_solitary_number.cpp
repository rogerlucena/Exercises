#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/single-number/

// Given an array of integers, every element appears twice except for one. Find that single one.
// Note: Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

// Great trick: remember that XOR is commutative and associative!
int singleNumber(const vector<int> &A) {
	if(A.size() == 0) {
		throw "Empty vector";
	}
	int ans = A[0];
	for(int i = 1; i < A.size(); ++i) {
		ans ^= A[i];
	} 

	return ans;
}

// Explanation: 
// you can transform any sequence of XORs in a sequence of 0s and 1s (and XOR operators between),
// then, any pair number of 0s or 1s cancels out to zero. We will have by the end (for every position):
//           0 XOR (the final odd bit) which is equal to the final bit that happened an odd number of times!!

int main() {
	vector<int> A = {1, 2, 2, 3, 1};
	cout << "Answer: " << singleNumber(A) << endl;
	return 0;
}