#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// https://www.interviewbit.com/problems/max-sum-contiguous-subarray/

// Find the contiguous subarray within an array A, of length N, which has the largest sum.
// Constraints:
// 1 <= N <= 1e6
// -1000 <= A[i] <= 1000

// Solution:
// https://youtu.be/ohHWQf1HDfU
// Brute force -> O(n^3): see all (i, j). Improvement: remember temp_sum(i, j-1) and just sum arr[j] to 
//     it in every iteration -> O(n^2)
// Divide and conquer -> O(n log n): T(n) = 2*T(n/2) + O(n), the last O(n) is to verify possible interval 
//     starting in the left and finishing in the right side (same complexity as merge sort)
//     Calculus: T(n) = ... = 4*T(n/4) + 2*O(n/2) + O(n) = ... = 2^(log n) * O(1) + n log n = O(n log n)
// Kadane's algorithm -> O(n): take advantage of the fact that there shall be no negative prefixes, genious trick

// Kadane's O(n) (beats 100% in runtime on Leetcode):
int maxSubArray(const vector<int> &A) {
	int sum = 0, ans = INT_MIN;
	for(int el : A) {
		sum = sum + el;
		ans = max(sum, ans);
		sum = max(sum, 0);
	}

	return ans;
}

// Divide and Conquer below (O(n log n), slower, beats only 5% in runtime on Leetcode):
int maxSubArrayRec(const vector<int> &nums, int start, int end) {
    if (start > end) {
        return INT_MIN;
    }

    if (start == end) {
        return nums[start];
    }

    if (end - start == 1) {
        return max({nums[start], nums[end], nums[start] + nums[end]});
    }

    int mid = start + (end - start) / 2;

    int maxL = maxSubArrayRec(nums, start, mid - 1);
    int maxR = maxSubArrayRec(nums, mid, end);

    int sumL = 0;
    int maxSumL = INT_MIN;
    for (int i = mid - 1; i >= start; --i) {
        sumL += nums[i];
        maxSumL = max(maxSumL, sumL);
    }

    int sumR = 0;
    int maxSumR = INT_MIN;
    for (int i = mid; i <= end; ++i) {
        sumR += nums[i];
        maxSumR = max(maxSumR, sumR);
    }

    return max({maxL, maxR, maxSumL + maxSumR});
}

int maxSubArray(vector<int> &nums) {
    return maxSubArrayRec(nums, 0, nums.size() - 1);
}

int main() {
	vector<int> v = {1, 2, 3, 4, -10}; // ans: 10
	// vector<int> v = {-2, 1, -3, 4, -1, 2, 1, -5, 4}; // ans: 6
	cout << maxSubArray(v) << endl;

	return 0;
}