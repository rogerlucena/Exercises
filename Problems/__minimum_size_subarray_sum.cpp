#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/minimum-size-subarray-sum
// https://leetcode.com/problems/minimum-size-subarray-sum
// Remember: note that we have only positive nums and a positive target -> thus can use sliding window to eliminate
// iterations that would not improve the answer (and then get linear instead of quadratic time complexity).
// Note: another solution in O(n log n) in time would build a vector prefixSum (size n+1) and for each possible start index "l" in [0, n)
// would do binary search in the prefixSum vector to find the smallest "r >= l" for which "prefixSum[r+1] - prefixSum[l] >= target" (if any - that is the sum of elements in [l,r]),
// and update min_len accordingly. Note that prefixSum[i] is the sum of the elements to the left of i (excluding i).
// Immediately say the quadratic solution out loud too so the interviewer already know that you got at least that and is just optimizing now.

// Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater
// than or equal to target. If there is no such subarray, return 0 instead.

// Example 1:
// Input: target = 7, nums = [2,3,1,2,4,3]
// Output: 2

// Example 2:
// Input: target = 4, nums = [1,4,4]
// Output: 1

// Constraints:
// 1 <= target <= 10^9
// 1 <= nums.length <= 10^5
// 1 <= nums[i] <= 10^4

// O(n) in time and O(1) in space.
// Website solution:
int minSubArrayLen(int target, vector<int>& nums) {
    int l = 0;
    int curr_sum = 0;
    int min_len = INT_MAX;

    for (int r = 0; r < nums.size(); ++r) {  // Interval [l, r].
        curr_sum += nums[r];
        while (curr_sum >= target) {
            min_len = min(min_len, r - l + 1);
            curr_sum -= nums[l];
            ++l;
        }
    }

    return min_len == INT_MAX ? 0 : min_len; 
}

// My solution a bit more complex:
int minSubArrayLenOlder(int target, vector<int>& nums) {
    int curr_sum = nums[0];
    int min_len = INT_MAX;
    int end = 0;
    
    for (int start = 0; start < nums.size(); ++start) {  // [start, end]
        while (end + 1 < nums.size() && curr_sum < target) {
            ++end;
            curr_sum += nums[end];
        }

        min_len = curr_sum >= target ? min(min_len, end - start + 1) : min_len;

        curr_sum -= nums[start];
    }

    return min_len == INT_MAX ? 0 : min_len;
}
// Small optional optimization inside the "while" above:
// if (min_len == 1 || (end == nums.size() - 1 && curr_sum < target)) {  // small optimization.
//     break;
// }

int main() {
	cout << "Hello, World!";
	return 0;
}