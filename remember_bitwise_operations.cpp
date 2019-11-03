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
	cout << (x & ~(x-1)) << endl; // extracts the lowest set bit of x (all others are clear)
	x = x | (x + 1); // x with the lowest cleared bit set.
	cout << ((x >> 2) & 1); // shows the bit at the 3rd position of "x"
	cout << (29 << 2) << endl << endl;

	// Other tricks:
	// x & ~(x-1) extracts the lowest set bit of x (all others are clear). Pretty patterns when applied to a linear sequence.
	// x & (x + (1 << n)) = x, with the run of set bits (possibly length 0) starting at bit n cleared.
	// x & ~(x + (1 << n)) = the run of set bits (possibly length 0) in x, starting at bit n.
	// x | ~(x + 1) = extracts the lowest cleared bit of x (all others are set).
	// x | (x - (1 << n)) = x, with the run of cleared bits (possibly length 0) starting at bit n set.
	// x | ~(x - (1 << n)) = the lowest run of cleared bits (possibly length 0) in x, starting at bit n are the only clear bits.


	// Bits manipulation:
	cout << "Bits manipulation - how to represent:" << endl;
	string binary = bitset<8>(64 + 5).to_string(); // to a 8-char string representing the binary form of the number
    cout << binary << endl;

    unsigned long ulongDecimal = std::bitset<8>(binary).to_ulong();
    cout << "ulong decimal: " << ulongDecimal << endl;
	
	int decimal = stoi(binary, nullptr, 2);
	cout << "int decimal: " << decimal << endl;

	return 0;
}