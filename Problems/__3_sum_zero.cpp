#include <iostream>
#include <vector>
#include <algorithm>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/3sum
// https://www.interviewbit.com/problems/3-sum-zero/
// (two pointer idea again)
// Remember: in the two sum problem (https://leetcode.com/problems/two-sum/) the array must be sorted, if not you can still
	// be O(N) in time keeping a hash map val-index after a first pass to try to find the complement wrt to target in the second pass
	// (can even do in only one pass with hash map, verifying as we go if the complement was already seen in the past) - but then will need extra space.

// Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0?
// Find all unique triplets in the array which gives the sum of zero.

// Note:
// Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
// The solution set must not contain duplicate triplets. For example, given array S = {-1 0 1 2 -1 -4}, A solution set is:
// (-1, 0, 1)
// (-1, -1, 2)

// O(N^2) instead of O(N^3) below. =]
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;

    for (int i = 0; i < nums.size() - 2; ++i) {
		if (nums[i] > 0) break;
		if (i > 0 && nums[i] == nums[i - 1]) continue;

        int target = -(nums[i]);
        for (int j = i + 1, k = nums.size() - 1; j < k;) {
            if (nums[j] + nums[k] == target) {
                ans.push_back({nums[i], nums[j], nums[k]});
                ++j;
                --k;
                while (j < k && nums[j] == nums[j - 1]) {  // to avoid repeated triplets, no need todo this for k as well; j < k to avoid out of bounds.
                    ++j;
                }
            } else if (nums[j] + nums[k] < target) {
                ++j;
            } else {
                --k;
            }
        }
    }

    return ans;
}

// Dirtier solution below.
int incrementTillDifferent(int j, vector<int> &A) {
	while(A[j+1] == A[j]) {
		++j;
	}
	return j+1;
}

int decrementTillDifferent(int k, vector<int> &A) {
	while(A[k-1] == A[k]) {
		--k;
	}
	return k-1;
}

vector<vector<int>> threeSumOld(vector<int> &A) {
	vector<vector<int>> ans = {};
	if(A.size() < 3) {
		return ans;
	}

	sort(A.begin(), A.end()); // A = {-4, -1, -1, 0, 1, 2}
	for(int i = 0; i < A.size()-2; i = incrementTillDifferent(i, A)) {
		int a = A[i];
		for(int j = i+1, k = A.size()-1; j < k; ) {
			int b = A[j];
			int c = A[k];
			int sum = a + b + c;
			if(sum == 0) {
				vector<int> ansElement = {a, b, c};
				ans.push_back(ansElement);
				j = incrementTillDifferent(j, A);
				k = decrementTillDifferent(k, A);
			} else if(sum < 0) {
				j = incrementTillDifferent(j, A);
			} else {
				k = decrementTillDifferent(k, A);
			}
		}
	}

	return ans;
}


int main() {
	vector<int> S = {-1, 0, 1, 2, -1, -4};
	cout << "Answer:" << endl;
	printMatrix(threeSum(S));
	return 0;
}