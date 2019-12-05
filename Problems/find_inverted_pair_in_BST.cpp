#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/recover-binary-search-tree/

// Two elements of a binary search tree (BST) are swapped by mistake.
// Tell us the 2 values swapping which the tree will be restored.

//  Note:
// A solution using O(n) space is pretty straight forward. Could you devise a constant space solution? 

// Example :

// Input : 
//          1
//         / \
//        2   3

// Output : 
//        [1, 2]

// Explanation : Swapping 1 and 2 will change the BST to be 
//          2
//         / \
//        1   3
// which is a valid BST   

int getGreatest(TreeNode* t) {
	if(!t) {
		return INT_MIN;
	}

	return max({t->val, getGreatest(t->left), getGreatest(t->right)});
}

int getSmallest(TreeNode* t) {
	if(!t) {
		return INT_MAX;
	}

	return min({t->val, getSmallest(t->left), getSmallest(t->right)});
}

vector<int> recoverTree(TreeNode* A) {
	if(!A) {
		return vector<int>();
	}

	int leftGreatest = A->left ? getGreatest(A->left) : A->val;
	int rightSmallest = A->right ? getSmallest(A->right) : A->val;

	vector<int> ans;
	if(leftGreatest > A->val && rightSmallest < A->val) {
		ans = {rightSmallest, leftGreatest};
	} else if(leftGreatest > A->val) {
		ans = {A->val, leftGreatest};
	} else if(rightSmallest < A->val) {
		ans = {rightSmallest, A->val};
	} else {
		ans = recoverTree(A->left);
		ans = !ans.empty() ? ans : recoverTree(A->right); 
	}
	
	return ans;
}


int main() {
	cout << "Hello, World!";
	return 0;
}