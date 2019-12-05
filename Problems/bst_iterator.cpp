#include <iostream>
#include <stack>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/bst-iterator/
// (the interesting here is to think about doing it using only O(h) in space, 
// instead of just doing an inorder traversal and saving everyone to an auxiliar vector - O(n) in space)

// Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

// The first call to next() will return the smallest number in BST. Calling next() again will return the next 
// smallest number in the BST, and so on.

// Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
// Try to optimize the additional space complexity apart from the amortized time complexity.

class BSTIterator {
public:
	BSTIterator(TreeNode *root);
	bool hasNext();
	int next(); 
};

stack<TreeNode*> st;

BSTIterator::BSTIterator(TreeNode *root) {
	st = stack<TreeNode*>();

	while (root) {
		st.push(root);
		root = root->left;	
	}
}

/** @return whether we have a next smallest number */
bool BSTIterator::hasNext() {
	return !st.empty();
}

/** @return the next smallest number */
int BSTIterator::next() {
	TreeNode* t = st.top();
	st.pop();
	int ans = t->val;

	if(t->right) {
		TreeNode* curr = t->right;
		while (curr) {
			st.push(curr);
			curr = curr->left;
		}
	}

	return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}