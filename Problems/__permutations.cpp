#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/permutations/

// Given a collection of numbers, return all possible permutations.

// Example:
// With [1,2,3] we will have the following permutations:
// [1,2,3]
// [1,3,2]
// [2,1,3] 
// [2,3,1] 
// [3,1,2] 
// [3,2,1]

// NOTE:
// No two entries in the permutation sequence should be the same.
// For the purpose of this problem, assume that all the numbers in the collection are unique.

// O(N*N!) in time (N! leaves and O(N) work per leaf to copy A to ans).
// Generally you can just think about the leaves as above and their work and you already get the correct assyntotic complexity.
// Branching factor here is the number of remaining available from [start, end), so N, N-1, N-2, ...
// The number of leaves dominates, so no need to stress about the number of intermediate nodes in the recursion tree and the work for each of them.
// But for the record for each depth k you have N!/(N-k)! nodes on the recursion tree for that level - summing for all levels you also get O(N!) nodes (ChatGPT calculated) and (N-k) work for each of them, so the leaves dominate (O(N*N!) total work).
// O(N*N!) in space as well (build ans).
void auxPermute(vector<int> &A, int start, vector<vector<int>> &ans) {
	if(start == A.size() - 1) {
		ans.push_back(A);
		return;
	}

	for(int i = start; i < A.size(); ++i) {
		swap(A[start], A[i]);
		auxPermute(A, start+1, ans);
		swap(A[start], A[i]);
	}
}

vector<vector<int>> permute(vector<int> &A) {
	vector<vector<int>> ans;
	if(A.size() == 0) {
		return ans;
	}

	// sort(A.begin(), A.end());
	auxPermute(A, 0, ans);

	return ans;

}

// The other solution below is slower but also the same asymptotic complexity of above as the leaves dominate.
// Note that for each intermediate level of the recursion tree the work here is O(N) and not O(N-k) as above (thus slower on Leetcode), 
// but the branching factor here still is (N-k) for each depth k, that is why we still have N! leaves with O(N) work for each (push_back to ans).
// Thus, final time ans space complexity here is also O(N*N!).
void permuteRecursive(vector<int>& nums, vector<int>& curr, unordered_set<int>& picked, vector<vector<int>>& ans) {
    if (curr.size() == nums.size()) {
        ans.push_back(curr);
        return;
    }

    for (int num : nums) {
        if (!picked.count(num)) {
            curr.push_back(num);
            picked.insert(num);
            permuteRecursive(nums, curr, picked, ans);
            curr.pop_back();
            picked.erase(num);
        }
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    unordered_set<int> picked;
    vector<int> curr = {};
    vector<vector<int>> ans = {};
    permuteRecursive(nums, curr, picked, ans);

    return ans;
}

int main() {
	vector<int> A = {1, 2, 3};
	for(vector<int> p : permute(A)) {
		printVector(p);
	}

	return 0;
}