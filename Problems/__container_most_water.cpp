#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/container-with-most-water/
// Good example for two index approach (can happen even in non-sorted arrays!):
// Start with the brute force and then analyze if you can optimize it - discard some 
// iterations that will not improve the result

// Given n non-negative integers a1, a2, ..., an,
// where each represents a point at coordinate (i, ai).
// 'n' vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0).
// Find two lines, which together with x-axis forms a container, such that the container contains the most water.

// Example:
// Input : [1, 5, 4, 3]
// Output : 6
// Explanation : 5 and 3 are distance 2 apart. So size of the base = 2. Height of container = min(5, 3) = 3. 
// So total area = 3 * 2 = 6

int maxArea(vector<int> &A) {
	int maxArea = 0;
	for(int i1 = 0, i2 = A.size()-1; i1 < i2; ) {
		int currArea = (i2-i1) * min(A[i1], A[i2]);
		if(currArea > maxArea) {
			maxArea = currArea;
		}
		if(A[i1] <= A[i2]) {
			++i1;
		} else {
			--i2;
		}
	}

	return maxArea;
}


int main() {
	vector<int> A = {1, 5, 4, 3};
	cout << "Answer: " << maxArea(A);

	return 0;
}