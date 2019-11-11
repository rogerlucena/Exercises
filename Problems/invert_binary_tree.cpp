#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/invert-the-binary-tree/

// Given a binary tree, invert the binary tree and return it.
// Look at the example for more details.

// Example:
// Given binary tree

//      1
//    /   \
//   2     3
//  / \   / \
// 4   5 6   7
// invert and return

//      1
//    /   \
//   3     2
//  / \   / \
// 7   6 5   4

TreeNode* invertTree(TreeNode* A) {
	if(!A) {
		return A;
	}

	A->left = invertTree(A->left);
	A->right = invertTree(A->right);

	TreeNode* tmp = A->left;
	A->left = A->right;
	A->right = tmp;

	return A;
}


int main() {
	cout << "Hello, World!";
	return 0;
}