#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/flatten-binary-tree-to-linked-list/

// Given a binary tree, flatten it to a linked list in-place.

// Example:

// Given
//          1
//         / \
//        2   5
//       / \   \
//      3   4   6

// The flattened tree should look like:
//    1
//     \
//      2
//       \
//        3
//         \
//          4
//           \
//            5
//             \
//              6

// Note that the left child of all nodes should be NULL.

TreeNode* getRightmost(TreeNode* t) {
	if(!t->right) {
		return t;
	}

	return getRightmost(t->right);
}

TreeNode* flatten(TreeNode* A) {
	if(!A || !(A->left || A->right)) {
		return A;
	}

	A->left = flatten(A->left);
	A->right = flatten(A->right);

	if(!A->left) {
		return A;
	}

	TreeNode* rightmostOfLeft = getRightmost(A->left);
	rightmostOfLeft->right = A->right;
	A->right = A->left;
	A->left = nullptr;

	return A;
}


int main() {
	cout << "Hello, World!";
	return 0;
}