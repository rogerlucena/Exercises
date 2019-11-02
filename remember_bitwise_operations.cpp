#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/tutorial/tricks-with-bits/

// Bitwise operations in C++
// & - and (&& is only for booleans - consider any non-zero number equals to true)
// | - or (|| is only for booleans)
// ^ - XOR
// ~ - not (ex: 0 => -1, 2 => -3, 3 => -4, 4 => -5 (x => -x-1) : flip the signal bit too)
// A << x - shifting the bits of A to the left by x positions; similar with >>
// ex:                 29 =  0 0 1 1 1 0 1 << 2
// 						     1 1 1 0 1 0 0  = 116 

int main() {
	int x = 4;

	// Tricks:
	x = x ^ 1; // change the least siginificant bit
	x = x & (x-1); // will clear the lowest set bit of x
	x = x | (x + 1); // x with the lowest cleared bit set.
	cout << ((x >> 2) & 1); // shows the bit at the 3rd position of "x"
	cout << (29 << 2) << endl;

	// Other tricks:
	// x & ~(x-1) extracts the lowest set bit of x (all others are clear). Pretty patterns when applied to a linear sequence.
	// x & (x + (1 << n)) = x, with the run of set bits (possibly length 0) starting at bit n cleared.
	// x & ~(x + (1 << n)) = the run of set bits (possibly length 0) in x, starting at bit n.
	// x | ~(x + 1) = extracts the lowest cleared bit of x (all others are set).
	// x | (x - (1 << n)) = x, with the run of cleared bits (possibly length 0) starting at bit n set.
	// x | ~(x - (1 << n)) = the lowest run of cleared bits (possibly length 0) in x, starting at bit n are the only clear bits.

	return 0;
}