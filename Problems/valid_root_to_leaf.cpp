#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/explore/other/card/30-day-leetcoding-challenge/532/week-5/3315/

// Given a binary tree where each path going from the root to any leaf form a valid sequence, 
// check if a given string is a valid sequence in such binary tree. 

// We get the given string from the concatenation of an array of integers arr and the concatenation 
// of all values of the nodes along a path results in a sequence in the given binary tree.

// Constraints:
// 1 <= arr.length <= 5000
// 0 <= arr[i] <= 9
// Each node's value is between [0 - 9].

bool isValid(TreeNode* root, const vector<int> &arr, int pos) {
	if(root == nullptr || root->val != arr[pos]) {
		return false;
	}

	if(pos == arr.size() - 1) {
		return root->left == nullptr && root->right == nullptr;
	}

	return isValid(root->left, arr, pos+1) || isValid(root->right, arr, pos+1);
}

bool isValidSequence(TreeNode* root, vector<int> &arr) {	
	return isValid(root, arr, 0);
}

int main() {
	cout << "Hello, World!";
	return 0;
}