#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/subsets
// https://neetcode.io/problems/subsets
// Remember: classic backtracking, attention that the runtime complexity here is O(N*2^N) and 
// not just O(2^N) -> we have 2^N leaves, 2^(N+1)-1 = O(2^N) call nodes (sum of P.G.), and push_back to ans is O(N) for each leaf.

// Given an array nums of unique integers, return all possible subsets of nums.
// The solution set must not contain duplicate subsets. You may return the solution in any order.

// Example 1:
// Input: nums = [1,2,3]
// Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

void subsetsRec(vector<int>& nums, int i, vector<int>& curr, vector<vector<int>>& ans) {
    if (i == nums.size()) {
        ans.push_back(curr); // remember O(N) in time here - do not forget this complexity.
        return;
    }

    subsetsRec(nums, i + 1, curr, ans);
    curr.push_back(nums[i]);
    subsetsRec(nums, i + 1, curr, ans);
    curr.pop_back();
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> curr = {};
    vector<vector<int>> ans = {};

    subsetsRec(nums, 0, curr, ans);
    return ans;
}

// Neat solution in lexographical order below:
// Below is O(N*2^N) in time as well (ChatGPT explained, branching factor always 2 for N times - only 
// deciding to include or not each number without reconsidering skipped ones).
// Do not think it is factorial - trap here (not reconsidering skipped ones). Remember that N! > 2^N for complexities.
void SubsetsRecursive(const vector<int>& A, int index, vector<int>& curr, vector<vector<int>>& ans) {
    ans.push_back(curr);

    for (int i = index; i < A.size(); ++i) {
        curr.push_back(A[i]);
        SubsetsRecursive(A, i+1, curr, ans);
        curr.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ans = {};
    vector<int> curr = {};

    SubsetsRecursive(nums, 0, curr, ans);
    return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}