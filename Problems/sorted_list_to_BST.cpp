#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/convert-sorted-list-to-binary-search-tree/

// Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

// A height balanced BST : a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1. 

// Example :
// Given A : 1 -> 2 -> 3
// A height balanced BST:
//       2
//     /   \
//    1     3

TreeNode* sortedListToBST(ListNode* A) {
	if(!A) {
		return nullptr;
	}

	int size = 0;
	ListNode* curr = A;
	while(curr) {
		++size;
		curr = curr->next;
	}

	curr = A;
	ListNode* prev = nullptr;
	int c = 0;
	while(c < size/2) {
		prev = curr;
		curr = curr->next;
		++c;
	}

	TreeNode* ans = new TreeNode(curr->val);
	if(prev) {
		prev->next = nullptr;
		TreeNode* left = sortedListToBST(A);
		TreeNode* right = sortedListToBST(curr->next);
		ans->left = left;
		ans->right = right;
	}

	return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}