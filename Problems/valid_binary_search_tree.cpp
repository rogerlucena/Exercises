#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/valid-binary-search-tree/

// Given a binary tree, determine if it is a valid binary search tree (BST).

// Assume a BST is defined as follows:

// The left subtree of a node contains only nodes with keys less than the node’s key.
// The right subtree of a node contains only nodes with keys greater than the node’s key.
// Both the left and right subtrees must also be binary search trees.

// Example:

// Input: 
//    1
//   /  \
//  2    3
// Output: 0 or False

// Input: 
//   2
//  / \
// 1   3
// Output: 1 or True 

// Return 0 / 1 ( 0 for false, 1 for true ) for this problem

// Website solution (elegant):
int check(TreeNode* A, int min, int max){
    if(A == nullptr) return 1;
    if(A->val < min || A->val > max) return 0;
    
    return (check(A->left, min, A->val-1) && check(A->right, A->val+1, max));
}

int isValidBST(TreeNode* A) {
    if(A == nullptr) return 1;
    return check(A, INT_MIN, INT_MAX);
}

// Old solution below:
int getRightmost(TreeNode* t) {
	if(!t->right) {
		return t->val;
	}
	return getRightmost(t->right);
}

int getLeftmost(TreeNode* t) {
	if(!t->left) {
		return t->val;
	}
	return getLeftmost(t->left);
}

int oldIsValidBST(TreeNode* A) {
	if(!A || (!A->left && !A->right)) {
		return 1;
	}

	bool left = true;
	if(A->left) {
		left = left && isValidBST(A->left);
		left = !left ? false : getRightmost(A->left) < A->val;
	}
	if(!left) {
		return 0;
	}

	bool right = true;
	if(A->right) {
		right = right && isValidBST(A->right);
		right = !right ? false : getLeftmost(A->right) > A->val;
	}
	if(!right) {
		return 0;
	}

	return 1;
}

int main() {
	cout << "Hello, World!";
	return 0;
}