#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://neetcode.io/problems/longest-increasing-subsequence
// https://leetcode.com/problems/longest-increasing-subsequence
// https://www.interviewbit.com/problems/longest-increasing-subsequence/
// Remember: you have to test all the elements j to the right of i and check LIS if nums[i] < nums[j],
// not only the next greater element to the right of i using a stack and going from right to left (gives wrong answer).
// 1D DP problem here, for memo think about memo[j] being the LIS using nums from j onwards including j.

// Find the longest increasing subsequence of a given array of integers, A.

// In other words, find a subsequence of array in which the subsequence’s elements are in strictly increasing order, 
// and in which the subsequence is as long as possible.
// This subsequence is not necessarily contiguous, or unique.
// In this case, we only care about the length of the longest increasing subsequence.

// Constraints:
// 1 <= length(A) <= 2500
// 1 <= A[i] <= 2000

// Example :
// Input 1:
//     A = [1, 2, 1, 5]
// Output 1:
//     3
// Explanation 1:
//     The sequence : [1, 2, 5]

// DP: try to divide into smaller recursive problems, if overlaps -> memoization
// go from right to left, iterate through the elements to the right bigger than "curr" using "memo", 
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> lis(n, 1);
    for (int i = n - 2; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            if (nums[i] < nums[j]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }

    return *max_element(lis.begin(), lis.end());
}

int main() {
	cout << "Hello, World!";
	return 0;
}