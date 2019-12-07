#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// https://www.interviewbit.com/problems/trailing-zeros-in-factorial/

// Given an integer n, return the number of trailing zeroes in n!.

// Note: Your solution should be in logarithmic time complexity.

// Example :

// n = 5
// n! = 120 
// Number of trailing zeros = 1
// So, return 1

int trailingZeroes(int A) {
    long two = 0;
    long five = 0;

	for(int i = 2; i <= A; i *= 2) {
		two += A/i;
	}

	for(int i = 5; i <= A; i *= 5) {
		five += A/i;
	}

    return (int) min(two, five);
}

int main() {
	// int A = 5; // ans: 1
	int A = 9247; // ans: 2307

	cout << "Answer: " << trailingZeroes(A) << endl;

	return 0;
}