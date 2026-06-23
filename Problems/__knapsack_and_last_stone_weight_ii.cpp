#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// last-stone-weight-ii problem (with similar 2D DP idea too) also below.

// KnapSack: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/

// Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total 
// value in the knapsack. 
// In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent 
// values and weights associated with n items respectively. Also given an integer W which represents knapsack capacity, 
// find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W

// Iterative KnapSack
int knapSack(int capacity, vector<int> &weights, vector<int> &val) {
	if(weights.size() == 0) {
		return 0;
	}

	// memo[i][j] = the max value possible using from position "i" on and current "weight" filled is j
	vector<vector<int>> memo(weights.size()+1, vector<int>(capacity+1 , -1));

	for(int i = weights.size(); i >= 0; --i) {
		for(int j = capacity; j >= 0; --j) {
			if(i == weights.size() || j == capacity) {
				memo[i][j] = 0;
			} else {
				memo[i][j] = memo[i+1][j]; // skip val[i]
				if(j + weights[i] <= capacity) {
					memo[i][j] = max(memo[i][j], val[i] + memo[i+1][j+weights[i]]); // uses val[i]
				}
			}
		}
	}

	return memo[0][0];
}

// Recursive KnapSack below
int knapSackHelper(int capacity, vector<int> &weights, vector<int> &val, int pos, int currWeight, vector<vector<int>> &memo) {
	if(pos == weights.size()) {
		return 0;
	}
	
	if(memo[pos][currWeight] != -1) {
		return memo[pos][currWeight];
	}

	memo[pos][currWeight] = knapSackHelper(capacity, weights, val, pos+1, currWeight, memo);
	if(currWeight + weights[pos] <= capacity) {
		memo[pos][currWeight] = max(memo[pos][currWeight], val[pos] + knapSackHelper(capacity, weights, val, pos+1, currWeight+weights[pos], memo));
	}

	return memo[pos][currWeight];
}

int recursiveKnapSack(int capacity, vector<int> &weights, vector<int> &val) {
	vector<vector<int>> memo(weights.size(), vector<int>(capacity+1 , -1));
	return knapSackHelper(capacity, weights, val, 0, 0, memo);
}


// https://neetcode.io/problems/last-stone-weight-ii
// https://leetcode.com/problems/last-stone-weight-ii
// Remember: 2D DP where one dimension is curr_sum (similar to knapsack problem).
// See the repeated recursion subproblems and thus the need for DP (eg: [1, 1, 1, _, _, _] -> arrives multiple times on i = 3 with same curr_sum).
// The constraints also give a hint as it shows that the total_sum is small (thus can use it as one dimension of the DP memo).

// You are given an array of integers stones where stones[i] is the weight of the ith stone.
// We are playing a game with the stones. On each turn, we choose any two stones and smash them together.
// Suppose the stones have weights x and y with x <= y. The result of this smash is:

// If x == y, both stones are destroyed, and
// If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
// At the end of the game, there is at most one stone left.

// Return the smallest possible weight of the left stone. If there are no stones left, return 0.

// Example:
// Input: stones = [2,4,1,5,6,3]
// Output: 1

// Constraints:
// 1 <= stones.length <= 30
// 1 <= stones[i] <= 100

// Returns the max sum of a subset of stones until i (exclusive) that is <= target.
// Suffix could be "Rec", "Tool", "Helper", etc ...
int lastStoneWeightIIHelper(int i, const vector<int>& stones, int curr_sum, const int target, vector<vector<int>>& memo) {
    if (i == stones.size() || curr_sum == target) {
        return curr_sum;
    }

    if (memo[i][curr_sum] != -1) {
        return memo[i][curr_sum];
    }

    memo[i][curr_sum] = lastStoneWeightIIHelper(i + 1, stones, curr_sum, target, memo);  // skip current stone.
    if (stones[i] + curr_sum <= target) {
        memo[i][curr_sum] = max(memo[i][curr_sum], lastStoneWeightIIHelper(i + 1, stones, stones[i] + curr_sum, target, memo));
    }

    return memo[i][curr_sum];
}

// O(n * m) in time and space, where m is the sum of the weights. 
// Idea: Equivalent to assigning + or - to each weight -> which is equivalent to finding a subset which sum is closest to total_sum / 2.
int lastStoneWeightII(vector<int>& stones) {
    int total_sum = accumulate(stones.begin(), stones.end(), 0);
    int target = total_sum / 2;
    vector<vector<int>> memo(stones.size(), vector<int>(target + 1, -1));
    int closest_to_target = lastStoneWeightIIHelper(0, stones, 0, target, memo);

    return total_sum - 2 * closest_to_target;  // the other_subset sum minus the found_subset sum.
}

// https://neetcode.io/problems/last-stone-weight
// https://leetcode.com/problems/last-stone-weight
// Easier version on which the two heaviest are always chosen and smashed y-x.
// O(n log n) in time and O(n) in space.
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> pq(stones.begin(), stones.end());  // max-heap.
    while (pq.size() > 1) {
        int max_1 = pq.top();
        pq.pop();
        int max_2 = pq.top();
        pq.pop();
        pq.push(max_1 - max_2);
    }

    return pq.top();
}

int main() {
	// vector<int> weights = {1, 1, 1};
	// vector<int> val = {10, 20, 30};
	// int capacity = 2; // ans: 50

    vector<int> weights = {10, 20, 30}; 
	vector<int> val = {60, 100, 120}; 
    int  capacity = 50; // ans: 220

	cout << "Answer: " << knapSack(capacity, weights, val) << endl;

	return 0;
}