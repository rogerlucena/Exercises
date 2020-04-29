#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/binary-tree-maximum-path-sum/
// Think from each node as if it was the upmost, separate one-side sum and the sum with both sides

// Given a non-empty binary tree, find the maximum path sum.

// For this problem, a path is defined as any sequence of nodes from some starting node 
// to any node in the tree along the parent-child connections. The path must contain at least 
// one node and does not need to go through the root.

// Example:
// Input: [-10,9,20,null,null,15,7]
//    -10
//    / \
//   9  20
//     /  \
//    15   7
// Output: 42

int maxPathWithNode(TreeNode* root, int &ans) {
	if(!root) {
		return 0;
	}

	int currSum = root->val;

	int left = maxPathWithNode(root->left, ans);
	int right = maxPathWithNode(root->right, ans);
	int maxSide = max(left, right);

	currSum = left > 0 ? currSum + left : currSum;
	currSum = right > 0 ? currSum + right : currSum;

	ans = max(ans, currSum);
	return root->val + (maxSide > 0 ? maxSide : 0);
}

int maxPathSum(TreeNode* root) {
	int ans = INT_MIN;
	maxPathWithNode(root, ans);
	
	return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}