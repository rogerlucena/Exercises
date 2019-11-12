#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/subtree-of-another-tree/

// Given two non-empty binary trees s and t, check whether tree t has exactly the 
// same structure and node values with a subtree of s. A subtree of s is a tree consists 
// of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

// Example 1:
// Given tree s:
//      3
//     / \
//    4   5
//   / \
//  1   2
// Given tree t:
//    4 
//   / \
//  1   2
// Return true, because t has the same structure and node values with a subtree of s.

// Example 2:
// Given tree s:
//      3
//     / \
//    4   5
//   / \
//  1   2
//     /
//    0
// Given tree t:
//    4
//   / \
//  1   2
// Return false.

bool isSameTree(TreeNode* s, TreeNode* t) {
	if(!s && !t) {
		return true;
	} 

	if(!s || !t) {
		return false;
	}

	return s->val == t->val && (isSameTree(s->left, t->left) && isSameTree(s->right, t->right));
}

bool isSubtree(TreeNode* s, TreeNode* t) {
	if(!t || isSameTree(s, t)) {
		return true;
	}
	
	if(s && isSubtree(s->left, t)) {
		return true;
	}
	
	return s && isSubtree(s->right, t);
}

int main() {
	cout << "Hello, World!";
	return 0;
}