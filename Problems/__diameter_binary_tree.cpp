#include <iostream>
#include <vector>
#include <unordered_map>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/diameter-of-binary-tree/
// Remember you can use a base case offset by 1 as here :D
// Other way: build a graph and do 2 BFSs, and the "diameter_tree" problem

// Given a binary tree, you need to compute the length of the diameter of the tree. The diameter 
// of a binary tree is the length of the longest path between any two nodes in a tree. This path may or 
// may not pass through the root.

// Example:
// Given a binary tree
//           1
//          / \
//         2   3
//        / \     
//       4   5    
// Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

// Note: The length of path between two nodes is represented by the number of edges between them.

// The idea below is to go through each node and analyze is as the "most top node" of the diameter path,
// keeping track of the maximum diameter as we go with the DFS
// O(N) in time and O(N) is space (max size of rec stack)
int height(TreeNode* root, int &ans) {
	if(!root) {
		return 0;
	}

	int L = height(root->left, ans);
	int R = height(root->right, ans);

	ans = max(ans, L+R+1);
	return 1 + max(L, R);

}

int diameterOfBinaryTree(TreeNode* root) {
	int ans = 1;
	height(root, ans);

	return ans-1; // the base case used here (null root) has not a number of edges (ans) of 0, the leaf node does (base case offset)
}

int main() {
	cout << "Hello, World!";
	return 0;
}