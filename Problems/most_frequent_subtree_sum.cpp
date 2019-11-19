#include <iostream>
#include <vector>
#include <unordered_map>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/most-frequent-subtree-sum/submissions/

// Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.

// Example 1
// Input:
//   5
//  /  \
// 2   -3
// return [2, -3, 4], since all the values happen only once, return all of them in any order.

// Example 2
// Input:
//   5
//  /  \
// 2   -5
// return [2], since 2 happens twice, however -5 only occur once.

// Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.

int fillWithSubtreeSums(TreeNode* root, unordered_map<int, int> &sums) {
	if(!root) {
		return 0;
	}

	int ans = root->val + fillWithSubtreeSums(root->left, sums) + fillWithSubtreeSums(root->right, sums);
	if(sums.find(ans) != sums.end()) {
		++sums[ans];
	} else {
		sums[ans] = 1;
	}

	return ans;
}

vector<int> findFrequentTreeSum(TreeNode* root) {
	if(!root) {
		return {};
	}

	unordered_map<int, int> sums;
	vector<int> ans;
	fillWithSubtreeSums(root, sums);

	int maxOcurrences = -1;
	for(pair<int, int> p : sums) {
		maxOcurrences = max(maxOcurrences, p.second);
	}

	for(pair<int, int> p : sums) {
		if(p.second == maxOcurrences) {
			ans.push_back(p.first);
		}
	}

	return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}