#include <iostream>
#include <vector>
#include <queue>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/level-order/

// Given a binary tree, return the level order traversal of its nodes’ values. (ie, from left to right, level by level).

// Example :
// Given binary tree

//     3
//    / \
//   9  20
//     /  \
//    15   7
// return its level order traversal as:

// [
//   [3],
//   [9,20],
//   [15,7]
// ]

// Also think about a version of the question where you are asked to do a level order traversal 
// of the tree when depth of the tree is much greater than number of nodes on a level.

vector<vector<int>> levelOrder(TreeNode* A) {
	vector<vector<int>> ans;
	if(!A) {
		return ans;
	}

	queue<pair<TreeNode*, int>> q;
	q.push({A, 0});
	while (!q.empty()) {
		pair<TreeNode*, int> nodeAndLevel = q.front();
		q.pop();
		TreeNode* node = nodeAndLevel.first;
		int level = nodeAndLevel.second;

		if(level >= ans.size()) {
			ans.push_back({node->val});
		} else {
			ans[level].push_back(node->val);
		}

		TreeNode* left = node->left;
		TreeNode* right = node->right;
		if(left) {
			q.push({left, level+1});
		}

		if(right) {
			q.push({right, level+1});
		}
	}

	return ans;
}


int main() {
	cout << "Hello, World!";
	return 0;
}