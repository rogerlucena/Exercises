#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/unique-binary-search-trees-ii/

// Given an integer A, how many structurally unique BST’s (binary search trees) exist that can store values 1…A?

// Constraints:
// 1 <= A <= 18

// Example:
// Input 1:
//     A = 3
// Output 1:
//     5
// Explanation 1:
//    1         3     3      2      1
//     \       /     /      / \      \
//      3     2     1      1   3      2
//     /     /       \                 \
//    2     1         2                 3

int numTreesHelper(int i, int j, vector<vector<int>> &memo) {
	if(i >= j) {
		return 1;
	}

	if(memo[i][j] != -1) {
		return memo[i][j];
	}

	memo[i][j] = 0;
	for(int k = i; k <= j; ++k) {
		int left = numTreesHelper(i, k-1, memo);
		int right = numTreesHelper(k+1, j, memo);
		memo[i][j] += left * right;
	}

	return memo[i][j];
}


int numTrees(int A) {
	vector<vector<int>> memo(A+1, vector<int>(A+1, -1));
	return numTreesHelper(1, A, memo);
}


int main() {
	int A = 3; // ans: 5
	cout << "Answer: " << numTrees(A);

	return 0;
}