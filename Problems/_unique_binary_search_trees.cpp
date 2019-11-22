#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/unique-binary-search-trees/

// Given A, generate all structurally unique BST’s (binary search trees) that store values 1…A.

// Constraints:
// 1 <= A <= 15

// Example:
// Input 1:
//     A = 3
// Output 1:
//    1         3     3      2      1
//     \       /     /      / \      \
//      3     2     1      1   3      2
//     /     /       \                 \
//    2     1         2                 3

vector<TreeNode*> generateTreesHelper(int s, int e, vector<vector<vector<TreeNode*>>> &memo) {
	vector<TreeNode*> ans;
	if(s > e) {
		ans.push_back(nullptr);
		return ans;
	}

	if(!memo[s][e].empty()) {
		return memo[s][e];
	}

	for(int i = s; i <= e; ++i) {
		for(TreeNode* l : generateTreesHelper(s, i-1, memo)) {
			for (TreeNode* r : generateTreesHelper(i+1, e, memo)) {
				TreeNode* h = new TreeNode(i);
				h->left = l;
				h->right = r;
				memo[s][e].push_back(h);
			}
		}
	}

	return memo[s][e];
}

vector<TreeNode*> generateTrees(int A) {
	vector<TreeNode*> trees;
	if(A < 1) {
		return trees;
	}

	vector<vector<vector<TreeNode*>>> memo(A+1, vector<vector<TreeNode*>>(A+1, vector<TreeNode*>()));
	return generateTreesHelper(1, A, memo);
}

int main() {
	cout << "Hello, World!";
	return 0;
}