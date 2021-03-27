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

// See _diameter_of_tree.cpp solution with 2 DFSs as well.

// The idea below is to go through each node and analyze is as the "most top node" of the diameter path,
// keeping track of the maximum diameter as we go with the DFS
// Time Complexity: O(N). We visit every node once.
// Space Complexity: O(N), the size of our implicit call stack during our depth-first search.
int height(TreeNode* root, int &ans) { // number of edges of the longest path to a leaf
	if(!root) {
		return -1;
	}

	int L = height(root->left, ans);
	int R = height(root->right, ans);

	ans = max(ans, L+R+2); // test it as the "top most node"
	return 1 + max(L, R);
}

int diameterOfBinaryTree(TreeNode* root) {
	int ans = 0;
	height(root, ans);

	return ans; // remember: previously we had a base case offset here -> we returned "ans-1"
}

int main() {
	cout << "Hello, World!";
	return 0;
}