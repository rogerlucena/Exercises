#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://www.interviewbit.com/problems/array-3-pointers/

// You are given 3 arrays A, B and C. All 3 of the arrays are sorted.
// Find i, j, k such that :
// max(abs(A[i] - B[j]), abs(B[j] - C[k]), abs(C[k] - A[i])) is minimized.

// Better approach than the one bellow:

// Windowing strategy works here.
// Lets say the arrays are A,B and C.
// Take 3 pointers X, Y and Z
// Initialize them to point to the start of arrays A, B and C
// Find min of X, Y and Z.
// Compute max(X, Y, Z) - min(X, Y, Z).
// If new result is less than current result, change it to the new result.
// Increment the pointer of the array which contains the minimum.
// Note that we increment the pointer of the array which has the minimum, because our goal is to decrease the difference.
// Increasing the maximum pointer is definitely going to increase the difference. Increase the second maximum pointer can 
// potentially increase the difference (if it passes the max number) - however, it certainly will not decrease the difference.

// Best solution: interviewBit 
int minimize(const vector<int> &a, const vector<int> &b, const vector<int> &c) {
	int diff = INT_MAX;
	int minimum = INT_MAX;
	int maximum = INT_MIN;
	int i, j, k;
	for(i = 0, j = 0, k = 0; i < a.size() && j < b.size() && k < c.size();) {
		minimum = min(a[i], min(b[j], c[k]));
		maximum = max(a[i], max(b[j], c[k]));
		diff = min(diff, maximum - minimum);
		if (diff == 0) break;
		if (a[i] == minimum) i++;
		else if (b[j] == minimum) j++;
		else k++;
	}
	return diff;
}

int minimizeForTheFirstVector(const vector<int> &A, const vector<int> &B, const vector<int> &C) {
	int minDistance = INT_MAX;
	for(int a : A) {
		auto itB = lower_bound(B.begin(), B.end(), a);
		itB = itB == B.end() || (itB != B.begin() && abs(*(itB-1) - a) < abs(*itB - a)) ? itB - 1 : itB;
		auto itC = lower_bound(C.begin(), C.end(), a);
		itC = itC == C.end() || (itC != C.begin() && abs(*(itC-1) - a) < abs(*itC - a)) ? itC - 1 : itC;
		
		int distanceAB = abs(a - (*itB));
		int distanceBC = abs((*itB) - (*itC));
		int distanceCA = abs((*itC) - a);

		int currDistance = max(distanceAB, distanceBC);
		currDistance = max(currDistance, distanceCA);

		minDistance = currDistance < minDistance ? currDistance : minDistance;
	}

	return minDistance;
}

int oldMinimize(const vector<int> &A, const vector<int> &B, const vector<int> &C) {
	int minA = minimizeForTheFirstVector(A, B, C);
	int minB = minimizeForTheFirstVector(B, C, A);
	int minC = minimizeForTheFirstVector(C, A, B);

	int overallMin = min(minA, minB);
	overallMin = min(overallMin, minC);

	return overallMin;
}

int main() {
	vector<int> A = {1, 4, 10};
	vector<int> B = {2, 15, 20};
	vector<int> C = {10, 12};
	cout << "Answer: " << minimize(A, B, C);

	return 0;
}