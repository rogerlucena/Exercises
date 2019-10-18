#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// https://www.interviewbit.com/problems/max-sum-contiguous-subarray/

// Find the contiguous subarray within an array, A of length N which has the largest sum.
// Constraints:
// 1 <= N <= 1e6
// -1000 <= A[i] <= 1000

// Solution:
// https://youtu.be/ohHWQf1HDfU
// Brute force -> O(n^3): see all (i, j). Improvement: remember temp_sum(i, j-1) and just sum arr[j] to it in every iteration -> O(n^2)
// Divide and conquer -> O(n log n): T(n) = 2*T(n/2) + O(n), the last O(n) is to verify possible interval starting in the left and finishing in the right side 
// Kadane's algorithm -> O(n): take advantage of the fact that there shall be no negative prefixes, genious trick

int maxSubArray(const vector<int> &A) {
	int sum = 0, ans = INT_MIN;
	for(int el : A) {
		sum = sum + el;
		ans = sum > ans ? sum : ans;
		sum = sum > 0 ? sum : 0;
	}

	return ans;
}

int main() {
	// vector<int> v = {1, 2, 3, 4, -10};
	vector<int> v = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
	cout << maxSubArray(v);
	return 0;
}