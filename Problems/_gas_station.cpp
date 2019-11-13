#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/gas-station/

// Given two integer arrays A and B of size N.
// There are N gas stations along a circular route, where the amount of gas at station i is A[i].

// You have a car with an unlimited gas tank and it costs B[i] of gas to travel from station i
// to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

// Return the minimum starting gas station’s index if you can travel around the circuit once, otherwise return -1.

// You can only travel in one direction. i to i+1, i+2, … n-1, 0, 1, 2.. Completing the circuit 
// means starting at i and ending up at i again.

// Example:
// Input 1:
//     A =  [1, 2]
//     B =  [2, 1]
// Output 1:
//     1
//     Explanation 1:
//         If you start from index 0, you can fill in A[0] = 1 amount of gas. Now your tank has 1 unit of gas. But you need B[0] = 2 gas to travel to station 1. 
//         If you start from index 1, you can fill in A[1] = 2 amount of gas. Now your tank has 2 units of gas. You need B[1] = 1 gas to get to station 0. So, you travel to station 0 and still have 1 unit of gas left over. You fill in A[0] = 1 unit of additional gas, making your current gas = 2. It costs you B[0] = 2 to get to station 1, which you do and complete the circuit.

// Website solution (elegant, O(n))
// A = gas, B = cost
int canCompleteCircuit(vector<int> &A, vector<int> &B) {
	int sumA = 0;
	int sumB = 0;
	int start = 0;
	int tank = 0;
	for (int i = 0; i < A.size(); ++i) {
		sumA += A[i];
		sumB += B[i];
		tank += A[i] - B[i];
		if (tank < 0) {
			start = i + 1; // (*) we do not need to try for "oldStart+1" till "i", "tank" will also be negative (for each index in this interval "A[i]-B[i]" is non-negative or negative with "abs(diff) < tank" at that moment, so you are still always reducing "tank" as you advance)
			tank = 0;
		}
	}

	if (sumA < sumB) { // if sumA >= sumB, we are assured that there is always a solution (otherwise we could use (*) and arrive in a contradiction)
		return -1;
	} else {
		return start; // if solution, here we have it since we tried for all all "i's" in ascending order ("start" will be stuck at the first one - smaller)
	}
}

// Old solution below:
bool canCompleteStartingHere(vector<int> &C, int index) {
	int acc = C[index];
	int i = (index+1) % C.size();

	while(i != index) {
		acc += C[i];
		if(acc < 0) {
			return false;
		}

		++i;
		i %= C.size();
	}

	return true;
}

int oldCanCompleteCircuit(const vector<int> &A, const vector<int> &B) {
	assert(A.size() == B.size());
	int N = A.size();
	if(N == 0) {
		return 1;
	}

	vector<int> C;
	for(int i = 0; i < N; ++i) {
		C.push_back(A[i] - B[i]);
	}

	for(int i = 0; i < N; ++i) {
		if (C[i] >= 0) {
			if(canCompleteStartingHere(C, i)) {
				return i;
			}
		}
	}	

	return -1;
}


int main() {
	vector<int> A = {684, 57, 602, 987};
	vector<int> B = {909, 535, 190, 976};
	cout << "Answer: " << canCompleteCircuit(A, B) << endl;

	return 0;
}