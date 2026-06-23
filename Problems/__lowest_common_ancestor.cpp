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

// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii
// Elegant solution for when having a parent node available:
// O(height) in time and O(1) in space.
TreeNode* lowestCommonAncestor(TreeNode* p, TreeNode* q) {
	// Handle edge case where either node is null
	if (!p || !q) return nullptr;

	TreeNode* a = p;
	TreeNode* b = q;

	while (a != b) {
		// Move to parent, or redirect to the other node if root is reached
		a = (a->parent != nullptr) ? a->parent : q;
		b = (b->parent != nullptr) ? b->parent : p;
	}

	return a;
}
// Why does it work?
// d1 = distance from p to LCA, d1 = same for q, c = distance from LCA to root.
// In the way above both pointers travel with speed 1 and on time (d1 + c + d2) will meet at the LCA (addition is commutative).
// Same algorithm for finding when 2 linked lists intersect.
// Insight form https://github.com/ovbystrova (Apple 2026).

int main() {
	cout << "Hello, World!";
	return 0;
}