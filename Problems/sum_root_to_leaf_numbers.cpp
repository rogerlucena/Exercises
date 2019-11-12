#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/sum-root-to-leaf-numbers/

// Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
// An example is the root-to-leaf path 1->2->3 which represents the number 123.

// Find the total sum of all root-to-leaf numbers % 1003.

// Example :
//     1
//    / \
//   2   3
// The root-to-leaf path 1->2 represents the number 12.
// The root-to-leaf path 1->3 represents the number 13.
// Return the sum = (12 + 13) % 1003 = 25 % 1003 = 25.

// Website solution (elegant):
int sumNumbers(TreeNode *root, int curSum) {
	if (root == NULL) return curSum;
	curSum = (curSum * 10 + root->val) % 1003;
	if (root->left == NULL && root->right == NULL) return curSum;
	if (!root->left) return sumNumbers(root->right, curSum);
	if (!root->right) return sumNumbers(root->left, curSum);
	return (sumNumbers(root->left, curSum) + sumNumbers(root->right, curSum)) % 1003;
}

int sumNumbers(TreeNode *A) {
	return sumNumbers(A, 0); 
}

// Old solution below:
// Remember: a*b mod n = (a mod n * b mod n) mod n
int getNumberDecimalBase(vector<int> &n) {
	int accum = 0;
	int multiplier = 1;
	for(int i = n.size()-1; i >= 0; --i) {
		accum += ((n[i] * multiplier) % 1003);
		accum %= 1003;
		multiplier *= 10;
		multiplier %= 1003;
	}

	return accum;
}

void generateListOfNumbers(TreeNode* A, vector<int> &currVector, vector<int> &listOfNumbers) {
	if(!A) {
		return;
	} else if(!A->left && !A->right) {
		currVector.push_back(A->val);
		int number = getNumberDecimalBase(currVector);
		listOfNumbers.push_back(number);
		currVector.pop_back();
		return;
	}

	currVector.push_back(A->val);
	generateListOfNumbers(A->left, currVector, listOfNumbers);
	generateListOfNumbers(A->right, currVector, listOfNumbers);
	currVector.pop_back();
}

int oldSumNumbers(TreeNode* A) {
	vector<int> listOfNumbers;
	vector<int> currVector;
	generateListOfNumbers(A, currVector, listOfNumbers);

	int ans = 0;
	for(int i : listOfNumbers) {
		ans += i;
		ans %= 1003;
	}

	return ans;
}


int main() {
	cout << "Hello, World!";
	return 0;
}