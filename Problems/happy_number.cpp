#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// https://leetcode.com/problems/happy-number/

// Write an algorithm to determine if a number is "happy".
// A happy number is a number defined by the following process: Starting with any positive integer, 
// replace the number by the sum of the squares of its digits, and repeat the process until the number 
// equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers 
// for which this process ends in 1 are happy numbers.

// Example: 

// Input: 19
// Output: true
// Explanation: 
// 12 + 92 = 82
// 82 + 22 = 68
// 62 + 82 = 100
// 12 + 02 + 02 = 1

int getSquaredDigitsSum(int n) {
	int ans = 0;
	// cout << "n: " << n << endl;

	int d = n % 10;
	for(int i = 0; n != 0; ++i) {
		ans += d * d;
		n = n / 10;
		d = n % 10;
	}
	// cout << "sqdsum: " << ans << endl << endl;
	return ans;
}

bool isHappy(int n) {
    unordered_set<int> seen;

	while(n != 1 && seen.find(n) == seen.end()) {
		seen.insert(n);
		n = getSquaredDigitsSum(n);
	}

	return n == 1;
}

int main() {
	int n = 19; // ans: True
	int ans = isHappy(n);
	cout << "Answer: " << ans << endl;

	return 0;
}