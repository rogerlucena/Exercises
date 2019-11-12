#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/sorted-array-to-balanced-bst/

// Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

// Balanced tree: a height-balanced binary tree is defined as a binary tree in which the depth of 
// the two subtrees of every node never differ by more than 1. 

// Example:
// Given A: [1, 2, 3]
// A height balanced BST : 
//       2
//     /   \
//    1     3

TreeNode* sortedArrayToBSTHelper(const vector<int> &A, int s, int e) { 
    if(s > e || s >= A.size() || e < 0) {
        return nullptr;
    } else if(s == e) {
        return new TreeNode(A[s]);
    }

    int midI = (e+s)/2;
    TreeNode* n = new TreeNode(A[midI]); 
    n->left = sortedArrayToBSTHelper(A, s, midI-1);
    n->right = sortedArrayToBSTHelper(A, midI+1, e);

    return n;
}

TreeNode* sortedArrayToBST(const vector<int> &A) {
    return sortedArrayToBSTHelper(A, 0, A.size()-1);
}

int main() {
	sortedArrayToBST({1, 2, 3, 4, 5});
	return 0;
}