#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/build-identical-trees/?test_id=9944

// Build Identical Trees
// Given two binary trees T1 and T2, you have to find minimum number of insertions to be done in T1 to make it structurally identical to T2. Return -1 if not possible.

// Notes:
// Assume insertions are done in a normal fashion in the BSTs.
// Assume while inserting, if the value of a node v is equal to value being inserted, we insert it in left subtree of node v.
// You can insert any positive or negative integer.

// Example:

// Input 1: 

// T1:       10
//          / \
//         9   20

// T2:       5
//          / \
//         2   7
//        /
//       1

// If you insert 8 into T1, it will be structurally identical to T2. Hence answer is 1.


// Input 2: 

// T1:       10
//          / \
//         9   20

// T2:       5
//            \
//             7

// You cannot make T1 and T2 structurally identical. Hence answer is -1.

void nEl(TreeNode* t, int &n) {
	if(!t) {
		return;
	}

	n += 1;
	nEl(t->left, n);
	nEl(t->right, n); 
}

int cntMatrix(TreeNode* A, TreeNode* B) {
	if(!A && !B) {
		return 0;
	}

	if(!A) {
		int nB = 0;
		nEl(B, nB);
		return nB; 
	}

	if(!B) {
		return -1;
	}

	int left = cntMatrix(A->left, B->left);
	int right = cntMatrix(A->right, B->right);

	if(left == -1 || right == -1) {
		return -1;
	}

	return left + right;
}