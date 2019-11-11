#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/min-depth-of-binary-tree/

// Given a binary tree, find its minimum depth.

// The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
// NOTE: The path has to end on a leaf node. 

// Example:
//          1
//         /
//        2
// min depth = 2.

int minDepth(TreeNode* A) {
	if(!A) {
		return 0;
	}

	if(A->left && !A->right) {
		return 1 + minDepth(A->left);
	} 

	if(A->right && !A->left) {
		return 1 + minDepth(A->right);
	}

	return 1 + min(minDepth(A->left), minDepth(A->right));
}

int main() {
	cout << "Hello, World!";
	return 0;
}