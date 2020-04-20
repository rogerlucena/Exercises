#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/

// Return the root node of a binary search tree that matches the given preorder traversal.

// (Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has
// a value < node.val, and any descendant of node.right has a value > node.val.  Also recall that a preorder 
// traversal displays the value of the node first, then traverses node.left, then traverses node.right.)

// Example:
// Input: [8,5,1,7,10,12]
// Output: [8,5,10,1,7,null,12]

TreeNode* bstFromPreorderInInterval(const vector<int> &preorder, int from, int to) {
	if(from > to) {
		return nullptr;
	}

	TreeNode* node = new TreeNode(preorder[from]);

	int startRightChild = from + 1;
	while(startRightChild <= to && preorder[startRightChild] < preorder[from]) {
		++startRightChild;
	}

	node->left = bstFromPreorderInInterval(preorder, from+1, startRightChild-1);
	node->right = bstFromPreorderInInterval(preorder, startRightChild, to);

	return node;
}

TreeNode* bstFromPreorder(vector<int> &preorder) {
    return bstFromPreorderInInterval(preorder, 0, preorder.size()-1);
}

int main() {
	cout << "Hello, World!";
	return 0;
}