#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/symmetric-tree/
// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

// For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3

// But the following [1,2,2,null,3,null,3] is not:

//     1
//    / \
//   2   2
//    \   \
//    3    3

bool isMirror(TreeNode* t1, TreeNode* t2) {
	if(!t1 || !t2) {
		return !t1 && !t2;
	}

	if(t1->val != t2->val) {
		return false;
	}

	return isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
}

bool isSymmetric(TreeNode* root) {
    if(!root) {
		return true;
	}
	return isMirror(root->left, root->right);
}

// Time complexity : O(n)O(n). Because we traverse the entire input tree once, the total run time is O(n)O(n), 
// where nn is the total number of nodes in the tree.

// Space complexity : The number of recursive calls is bound by the height of the tree. In the worst case, the tree is 
// linear and the height is in O(n)O(n). Therefore, space complexity due to recursive calls on the stack is O(n)O(n) in the worst case.

int main() {
	cout << "Hello, World!";
	return 0;
}