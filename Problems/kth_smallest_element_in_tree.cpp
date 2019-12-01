#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/kth-smallest-element-in-tree/

// Given a binary search tree, write a function to find the kth smallest element in the tree.

// Example :

// Input : 
//   2
//  / \
// 1   3

// and k = 2

// Return : 2

// As 2 is the second smallest element in the tree.
// NOTE : You may assume 1 <= k <= Total number of nodes in BST 

int kthsmallestHelper(TreeNode* t, int &k) {
	if(!t) {
		return 0;
	}

	int left = kthsmallestHelper(t->left, k);
	if(k <= 0) {
		return left;
	}

	if(--k == 0) {
		return t->val;
	}

	return kthsmallestHelper(t->right, k);
}

int kthsmallest(TreeNode* A, int B) {
	return kthsmallestHelper(A, B);
}

int main() {
	cout << "Hello, World!";
	return 0;
}