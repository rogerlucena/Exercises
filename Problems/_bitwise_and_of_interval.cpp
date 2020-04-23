#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// https://leetcode.com/problems/bitwise-and-of-numbers-range/
// Idea: think about each non-zero bit of m, find out if a number with bit 0 at that 
// position is in the interval

// Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of 
// all numbers in this range, inclusive.

// Example:
// Input: [5,7]
// Output: 4

// Note: do better than just "&"" all the numbers

// Get the smallest number greater than "num" that has a bit 0 at position "p"
inline long getNextWith0AtPos(long num, int p) {
	long ans = (num & (~( (1 << p) - 1))) + (1 << p);
	return ans;
}

int rangeBitwiseAnd(int m, int n) {
	if(m == 0 || m == n) {
		return m;
	}

	int nDigits = (int) log2(n) + 1;
	int ans = 0;
	for(int i = 1; i < nDigits; ++i) { // m: 101
		if( (((m >> i) & 1) == 1) && getNextWith0AtPos(m, i) > n) {
			ans |= (1 << i);
		}
	}

	return ans;
}

int main() {
	int m = 5, n = 7; // ans: 4
	// int m = 2147483646, n = 2147483647; // ans: 2147483646

	cout << "Answer: " << rangeBitwiseAnd(m, n) << endl;
	return 0;
}