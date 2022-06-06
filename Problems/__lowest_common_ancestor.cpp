#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

// Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
// According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes
// p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if(!root) {
		return nullptr;
	}
	
	if (root->val == p->val || root->val == q->val) {
		return root;
	}

	TreeNode* leftLca = lowestCommonAncestor(root->left, p, q);
	TreeNode* rightLca = lowestCommonAncestor(root->right, p, q);
	if (leftLca && rightLca) {
		return root;
	}

	return leftLca ? leftLca : rightLca;
}


int main() {
	cout << "Hello, World!";
	return 0;
}