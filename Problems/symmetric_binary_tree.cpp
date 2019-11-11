#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/symmetric-binary-tree/

// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

// Example :

//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3
// The above binary tree is symmetric.
// But the following is not:

//     1
//    / \
//   2   2
//    \   \
//    3    3

// Return 0 / 1 ( 0 for false, 1 for true ) for this problem

// Other idea: see if r->left->val == r->right->val; symmetric(r->left->left, r->right->right)
// 											         && symmetric(r->left->right, r->right->left)

bool isSymmetricVector(vector<int> v1, vector<int> v2) {
	if(v1.size() != v2.size()) {
		return false;
	}

	int size = v1.size();
	for(int i = 0; i < size; ++i) {
		if(v1[i] != v2[(size-1)-i]) {
			return false;
		}
	}

	return true;
}

void inorder(TreeNode* t, vector<int> &ans) {
	if(!t) {
		return;
	}

	inorder(t->left, ans);
	ans.push_back(t->val);
	inorder(t->right, ans);
}

int isSymmetric(TreeNode* A) {
	if(!A) {
		return 1;
	}

	vector<int> leftInorder, rightInorder;
	inorder(A->left, leftInorder);
	inorder(A->right, rightInorder);

	return isSymmetricVector(leftInorder, rightInorder) ? 1 : 0;
}

int main() {
	cout << "Hello, World!";
	return 0;
}