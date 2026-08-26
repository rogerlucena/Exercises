#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/combination-target-sum
// https://leetcode.com/problems/combination-sum
// Remember: neat example of when to use backtracking. See version II (with duplicates) also
// below in Python (check its time complexity reasoning below too - similar complexity reasoning in __subsets.cpp).

/*
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of
candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency
of at least one of the chosen numbers is different.

The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Example 1:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Example 2:
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
Input: candidates = [2], target = 1
Output: []

Constraints:
All elements of candidates are distinct.
1 <= candidates.length <= 30
2 <= candidates[i] <= 40
1 <= target <= 40
*/

// Time complexity: O(2^(t/m)) where t is the given target and m is the minimum value in nums.
// Space complexity: O(t/m) (max size of the recursion stack and of curr_sol).
// Note: all elements of nums are distinct (to avoid duplicated solutions) and target is > 0.
void combinationSumHelper(const vector<int>& nums, int target, int i, vector<int>& curr_sol, vector<vector<int>>& ans) {
	if (target == 0) {
		ans.push_back(curr_sol);
		return;
	}
	if (target < 0 || i == nums.size()) {  // remember < 0 case here (otherwise stack overflow).
		return;
	}

	// Add one of it and keep index "i" to allow more push_backs of that same number down the road.
	curr_sol.push_back(nums[i]);
	combinationSumHelper(nums, target - nums[i], i, curr_sol, ans);
	curr_sol.pop_back();

	// Now consider skipping it (do this as the second step for the final ans to be in lexicographical order).
	combinationSumHelper(nums, target, i + 1, curr_sol, ans);
}

vector<vector<int>> combinationSum(vector<int>& nums, int target) {
	vector<vector<int>> ans = {};
	vector<int> curr_sol = {};

	combinationSumHelper(nums, target, 0, curr_sol, ans);
	return ans;
}


// Unecessarily more complex and less elegant.
void combinationSumHelperOlderVersion(const vector<int>& nums, int target, int i, vector<int>& curr_sol, vector<vector<int>>& ans) {
	if (target == 0) {
		ans.push_back(curr_sol);
		return;
	}
	if (i == nums.size()) {
		return;
	}

	combinationSumHelper(nums, target, i + 1, curr_sol, ans);
	for (int n_i_used = 1; n_i_used <= target / nums[i]; ++n_i_used) {  // no need to do this here, can just push_back and call as above and keep index and then pop_back (more elegant/concise - in spite of this version having better runtime percentage than the other above on LeetCode).
		curr_sol.push_back(nums[i]);
		combinationSumHelper(nums, target - n_i_used * nums[i], i + 1, curr_sol, ans);
	}
	for (int n_i_used = 1; n_i_used <= target / nums[i]; ++n_i_used) {
		curr_sol.pop_back();
	}
}

int main() {
	cout << "Hello, World!";
	return 0;
}


/*
Follow-up Combination Sum II (in Python):

# https://neetcode.io/problems/combination-target-sum-ii
# https://leetcode.com/problems/combination-sum-ii
# Remember: backtracking - either sort and when skipping do skip till a different number is seen (to avoid duplications), 
# or use a hash map to count frequencies and pass only its keys (unique candidates) and their counts to the recursive helper.
# Note that in the first case the recursion branch goes in depth first adding all repetitions of a value, and then backtracks
# removing one repetitition at a time from backwards (to avoid repeated solutions doing the skipping with `while` as below).

# Same as "Combination Sum I" but possibly having duplicates inside `candidates` now.

# Example 1:
# Input: candidates = [9,2,2,4,6,1,5], target = 8
# Output: [
#   [1,2,5],
#   [2,2,4],
#   [2,6]
# ]

# Time complexity: O(n * 2^n) - note the difference from the case I above where an unlimited use of a candidate was allowed.
# (We have at most O(2^n) leaves (all different elements) and each does a O(n) append - note that we have O(2^n) intermediate nodes but each have a constant complexity that loses to the O(n) append from the leaves).
# Another way of seeing (thinking through each recursion branch - from Claude): "Summing over all the intermediate (non-leaf) nodes on the way down adds roughly a factor of the recursion depth (≤ n), and each time target == 0 is hit (leaf) we pay O(n) to copy curr[:] into ans (so the complexity is dominated by the leaves, which are 2^n at worst costing O(n) each)".
# Space complexity: O(n) extra space, O(n * 2^n) if the output storage is included.
class Solution:
    def combinationSum2(self, candidates: list[int], target: int) -> list[list[int]]:
        curr, ans = [], []
        candidates.sort()  # Essential in this case with repetitions to group them together (unless you use a Counter to keep track - below).
        self.combinationSum2Helper(candidates, target, 0, curr, ans)
        return ans

    def combinationSum2Helper(self, candidates: list[int], target: int, pos: int, curr: list[int], ans: list[list[int]]) -> None:
        if target == 0:
            ans.append(curr[:])  # Slicing is important here to append a snapshot of curr and not its object reference (remember this for the time complexity too!).
            return

        if pos >= len(candidates) or target < 0:
            return

        # Consider the appending case first if you want lexicographical ordered solution.
        curr.append(candidates[pos])
        self.combinationSum2Helper(candidates, target - candidates[pos], pos + 1, curr, ans)
        curr.pop()

        while pos + 1 < len(candidates) and candidates[pos + 1] == candidates[pos]:  # To avoid repetitions (when skipping do this until a different number is found).
            pos += 1
        self.combinationSum2Helper(candidates, target, pos + 1, curr, ans)

from collections import Counter 

class SolutionHashMap:
    def combinationSum2(self, candidates: list[int], target: int) -> list[list[int]]:
        curr, ans = [], []
        c = Counter(candidates)
        self.combinationSum2Helper(list(c.keys()), target, 0, curr, ans, c)  # Passing only the unique candidates - had to convert to `list` here to use [] on it later.
        return ans

    def combinationSum2Helper(self, unique_candidates: list[int], target: int, pos: int, curr: list[int], ans: list[list[int]], c: Counter[int]) -> None:
            if target == 0:
                ans.append(curr[:])
                return
    
            if pos >= len(unique_candidates) or target < 0:
                return

            # Consider adding unique_candidates[pos] if its count is positive.
            if c[unique_candidates[pos]] > 0:
                c[unique_candidates[pos]] -= 1
                curr.append(unique_candidates[pos])
                self.combinationSum2Helper(unique_candidates, target - unique_candidates[pos], pos, curr, ans, c)  # Keeping same index pos to allow to reuse it while its count is positive.
                curr.pop()
                c[unique_candidates[pos]] += 1
                # Note that if you decrement the counter and never increment it back, that reduction leaks into completely unrelated recursion
                # branches explored later, which have no business being affected by a choice made in a branch that's already been abandoned - yielding wrong result.
                # eg: candidates=[2,2,3], target=5 (so the only valid combination is [2,3]). With the restore line deleted:
                # Deep path picks both 2's (curr=[2,2]), then tries the 3: 2+2+3=7, overshoots (target<0), backs out — but c[3] is left at 0.
                # Backtrack to curr=[2] and try adding 3 again, but c[3] is still 0 (from the previous recursion branch) and then the solution [2, 3] is never found nor appended to `ans`.

            # Skip unique_candidates[pos] (next index is a different number).
            self.combinationSum2Helper(unique_candidates, target, pos + 1, curr, ans, c)
*/