#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://www.interviewbit.com/problems/3-sum/
// (two pointer idea again here)

// Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target.
// Return the sum of the three integers.
// (Assume that there will only be one solution)

// Example:
// given array S = {-1 2 1 -4},
// and target = 1.
// The sum that is closest to the target is 2. (-1 + 2 + 1 = 2)

int threeSumClosest(vector<int> &A, int B) {
	if(A.size() < 3) {
		throw "Size of the array must be at least 3";
	}

	sort(A.begin(), A.end());
	int closestSum = 0;
	int minDistance = INT_MAX;
	for(int i = 0; i < A.size()-2; ++i) {
		int target = B - A[i];
		for(int j = i+1, k = A.size()-1; j < k; ) {
			int currSum = A[j] + A[k];
			if(currSum == target) {
				return B;
			} else if(currSum > target) {
				--k;
			} else {
				++j;
			}

			int currDistance = abs(target - currSum);
			if(currDistance < minDistance) {
				closestSum = currSum + A[i];
				minDistance = currDistance;
			}
		}
	}

	return closestSum;
}


int main() {
	vector<int> A = {-1, 2, 1, -4};
	int target = 1;

	cout << "Answer: " << threeSumClosest(A, target) << endl;

	return 0;
}