#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://www.interviewbit.com/problems/stairs/

// You are climbing a stair case and it takes A steps to reach to the top.
// Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

// Example:
// Input:
// 	 A = 3 
// Output:
// 	 3 
// Explanation: 
// 	 [1 1 1], [1 2], [2 1]

// It is like a Fibonacci, you can do it even with no additional space at all
int climbStairsHelper(int A, unordered_map<int, int> &m) {
	if(A == 0 || A == 1 || A == 2) {
		m[A] = A;
		return m[A];
	}

	int aMinus1 = m.find(A-1) != m.end() ? m[A-1] : climbStairsHelper(A-1, m);
	int aMinus2 = m.find(A-2) != m.end() ? m[A-2] : climbStairsHelper(A-2, m);

	m[A] = aMinus1 + aMinus2;
	return m[A];
}

int climbStairs(int A) {
	unordered_map<int, int> m;
	return climbStairsHelper(A, m);
}


int main() {
	int A = 3;
	cout << "Answer: " << climbStairs(A) << endl;

	return 0;
}