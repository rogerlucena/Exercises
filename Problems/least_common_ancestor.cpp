#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/least-common-ancestor/

// Find the lowest common ancestor in an unordered binary tree given two values in the tree.

// Lowest common ancestor : the lowest common ancestor (LCA) of two nodes v and w in a tree or directed acyclic graph (DAG) is the lowest (i.e. deepest) node that has both v and w as descendants. 

// Example:
//         _______3______
//        /              \
//     ___5__          ___1__
//    /      \        /      \
//    6      _2_     0        8
//          /   \
//          7    4
// For the above tree, the LCA of nodes 5 and 1 is 3.

// LCA = Lowest common ancestor 
// Please note that LCA for nodes 5 and 4 is 5.

// You are given 2 values. Find the lowest common ancestor of the two nodes represented by val1 and val2
// No guarantee that val1 and val2 exist in the tree. If one value doesn’t exist in the tree then return -1.
// There are no duplicate values.
// You can use extra memory, helper functions, and can modify the node struct but, you can’t add a parent pointer.

void saveIfFoundBC(TreeNode* A, int B, int C, unordered_map<int, pair<bool, bool>> &foundBC) {
	if(A == nullptr) {
		return;
	}

	saveIfFoundBC(A->left, B, C, foundBC);
	saveIfFoundBC(A->right, B, C, foundBC);

	bool foundB = A->val == B || (A->left && foundBC[A->left->val].first) || ((A->right) && foundBC[A->right->val].first);
	bool foundC = A->val == C || (A->left && foundBC[A->left->val].second) || ((A->right) && foundBC[A->right->val].second);

	foundBC[A->val] = {foundB, foundC};
}

stack<int> getBFSStacked(TreeNode* t) {
	stack<int> s;
	if(!t) {
		return s;
	}

	queue<TreeNode*> q ({t});
	while(!q.empty()) {
		TreeNode* node = q.front();
		q.pop();
		s.push(node->val);

		if(node->left) {
			q.push(node->left);
		}

		if(node->right) {
			q.push(node->right);
		}
	}

	return s;
}

int lca(TreeNode* A, int B, int C) {
	unordered_map<int, pair<bool, bool>> foundBC;
	saveIfFoundBC(A, B, C, foundBC);

	stack<int> bfsStacked = getBFSStacked(A);

	while(!bfsStacked.empty()) {
		int nodeVal = bfsStacked.top();
		bfsStacked.pop();
		if(foundBC[nodeVal].first && foundBC[nodeVal].second) {
			return nodeVal;
		}
	}

	return -1;
}

int main() {
	cout << "Hello, World!";
	return 0;
}