#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/count-complete-tree-nodes
// Remember: from My Notes.txt - in a completely filled Binary Tree (all levels filled) the total number of nodes is 2^(h + 1) - 1.
// In a "Complete Binary Tree" both children are also "Complete", and at least one of them is completely filled.

// Given the root of a complete binary tree, return the number of the nodes in the tree.

// According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, 
// and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

// Design an algorithm that runs in less than O(n) time complexity.

// O(log n * log n) in time (log n recursive calls in the worst case with each having log n time complexity to get the "height+1" here).
// O(log n) in space (recursive stack).
int countNodesRecursive(TreeNode* root, int l = 1, int r = 1) {
    if (!root) {
        return 0;
    }

    TreeNode* left = root->left;
    TreeNode* right = root->right;
    while(left) {  // log n.
        ++l;
        left = left->left;
    }
    while(right) {  // log n.
        ++r;
        right = right->right;
    }

    if (l == r) {  // if root was a completely filled tree it stops the exploration already here (only log n in time) - it skips entire perfect subtrees without traversing all their nodes.
        return (1 << l) - 1;  // l here is (height + 1) already (see My Notes).
    }

    return 1 + countNodesRecursive(root->left) + countNodesRecursive(root->right);  // at least one of the children will be completely filled (property of Complete Binary Tree), so by the end it will actually explore only one of the children and not both.
}

int countNodes(TreeNode* root) {
    return countNodesRecursive(root);
}

int main() {
	cout << "Hello, World!";
	return 0;
}