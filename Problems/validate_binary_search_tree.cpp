#include <iostream>
#include <vector>
#include "tools.cpp"

using namespace std;

// https://neetcode.io/problems/valid-binary-search-tree
// https://leetcode.com/problems/validate-binary-search-tree
// Review: BST each node val is unique, descendants are "strictly" less or greater. LONG_MIN and LONG_MAX here instead of INT_MIN.

// Given the root of a binary tree, determine if it is a valid binary search tree (BST).

// A valid BST is defined as follows:

// The left subtree of a node contains only nodes with keys strictly less than the node's key.
// The right subtree of a node contains only nodes with keys strictly greater than the node's key.
// Both the left and right subtrees must also be binary search trees.

// Example 1:
// Input: root = [2,1,3]
// Output: true

// Constraints:
// The number of nodes in the tree is in the range [1, 10^4].
// -2^31 <= Node.val <= 2^31 - 1

bool isValidBSTDfs(TreeNode* root, long lower_bound, long upper_bound) {
    if (!root) {
        return true;
    }

    if (!(root->val > lower_bound && root->val < upper_bound)) {
        return false;
    }

    return isValidBSTDfs(root->left, lower_bound, root->val) &&
           isValidBSTDfs(root->right, root->val, upper_bound);
}

bool isValidBST(TreeNode* root) {
	return isValidBSTDfs(root, LONG_MIN, LONG_MAX);
}

int main() {
	cout << "Hello, World!";
	return 0;
}