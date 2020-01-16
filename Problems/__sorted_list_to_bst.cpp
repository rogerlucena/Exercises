#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
// key interest here: see the space complexity being defined only by the recursion stack max size
// 		do not forget the size of the rec stack on an interview!! if possible, say tail recursive

// Convert Sorted List to Binary Search Tree
// Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
// For this problem, a height-balanced binary tree is defined as a binary tree in which 
// the depth of the two subtrees of every node never differ by more than 1.

// Example:
// Given the sorted linked list: [-10,-3,0,5,9],
// One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
//       0
//      / \
//    -3   9
//    /   /
//  -10  5

// Version without using an auxiliar vector below:
// Every element only once -> O(N) in time
// O(log N) in space -> only size of the recursion stack (at most equal to the height of our BST)
// (cool: after calling for left, head will point exactly to root, inorder perfect here)
TreeNode* toBST(ListNode* &head, int start, int end) {
	if(start > end) {
		return nullptr;
	}

	int mid = (start+end)/2;
	
	TreeNode* left = toBST(head, start, mid-1);

	TreeNode* ans = new TreeNode(head->val); // after calling for left, head will point exactly to root :D
	head = head->next;
	ans->left = left;

	ans->right = toBST(head, mid+1, end);

	return ans;
}

TreeNode* sortedListToBST(ListNode* head) {
    int size = 0;
	ListNode* tmp = head;
	while(tmp) {
		++size;
		tmp = tmp->next;
	}

	return toBST(head, 0, size-1);
}


// Version using an auxiliar vector below (O(N) space and time too):
TreeNode* toBSTold(const vector<int> &v, int i, int j) {
	if(i>j) {
		return nullptr;
	}

	if(i == j) {
		return new TreeNode(v[i]);
	}

	int mid = (i+j)/2;
	TreeNode* ans = new TreeNode(v[mid]);
	ans->left = toBST(v, i, mid-1);
	ans->right = toBST(v, mid+1, j);

	return ans;
}

TreeNode* sortedListToBSTold(ListNode* head) {
	if(!head) {
		return nullptr;
	}

	vector<int> v;
	while(head) {
		v.push_back(head->val);
		head = head->next;
	}

	return toBST(v, 0, v.size()-1);
}

int main() {
	return 0;
}