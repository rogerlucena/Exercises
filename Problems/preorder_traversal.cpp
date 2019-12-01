#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/preorder-traversal/

// Given a binary tree, return the preorder traversal of its nodes’ values.

// Example:
// Given binary tree
//    1
//     \
//      2
//     /
//    3
// return [1,2,3].

void preorder(TreeNode* t, vector<int> &ans) {
	if(!t) {
		return;
	}

	ans.push_back(t->val);
	preorder(t->left, ans);
	preorder(t->right, ans);
}

vector<int> preorderTraversal(TreeNode* A) {
	vector<int> ans;
	preorder(A, ans);

	return ans;
}


int main() {
	cout << "Hello, World!";
	return 0;
}