#include <iostream>
#include <vector>

using namespace std;

// Problem and solution for subsets with duplicates is also below!

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
        SubsetsRecursive(A, i + 1, curr, ans);
        curr.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ans = {};
    vector<int> curr = {};

    SubsetsRecursive(nums, 0, curr, ans);
    return ans;
}


// Subsets with duplicates below:
// Remember: sort the input is key here and does not worsen complexity.
// https://neetcode.io/problems/subsets-ii
// https://leetcode.com/problems/subsets-ii

// You are given an array nums of integers, which may contain duplicates. Return all possible subsets.
// The solution must not contain duplicate subsets. You may return the solution in any order.

// Example 1:
// Input: nums = [1,2,1]
// Output: [[],[1],[1,2],[1,1],[1,2,1],[2]]

// O(N*2^N) in time as well.
// O(N) extra space and O(N*2^N) space for ans.
void subsetsWithDupRecursive(vector<int>& nums, int i, vector<int>& curr, vector<vector<int>>& ans) {
    if (i == nums.size()) {
        ans.push_back(curr);
        return;
    }

    curr.push_back(nums[i]);
    subsetsWithDupRecursive(nums, i + 1, curr, ans);
    curr.pop_back();

    while ((i + 1) < nums.size() && nums[i + 1] == nums[i]) {
        ++i;
    }
    subsetsWithDupRecursive(nums, i + 1, curr, ans);
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());       
    vector<int> curr;
    vector<vector<int>> ans;
    subsetsWithDupRecursive(nums, 0, curr, ans);

    return ans;
}

// Alternative neat solution to preserve lexicographical order below:
void auxSubsetsWithDup(vector<int> &A, vector<int> &currVector, int index, vector<vector<int>> &ans) {
    ans.push_back(currVector);

    for(int i = index; i < A.size(); ++i) {
        currVector.push_back(A[i]);
        auxSubsetsWithDup(A, currVector, i + 1, ans);
        currVector.pop_back();

        while (i + 1 < A.size() && A[i + 1] == A[i]) {
            ++i;
        }
    }
}

vector<vector<int>> subsetsWithDup(vector<int> &A) {
    vector<vector<int>> ans = {};

    sort(A.begin(), A.end());
    vector<int> currVector = {};
    auxSubsetsWithDup(A, currVector, 0, ans);

    return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}