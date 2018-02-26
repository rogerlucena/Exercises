#include <iostream>
#include <vector>

using namespace std;

/*

 Find the k-th smallest element of a BST.

 https://leetcode.com/explore/interview/card/top-interview-questions-medium/108/trees-and-graphs/790/

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  void getKth(TreeNode* root, int k, int &curr, int &kth) {
    if(root == NULL)
      return;
    getKth(root->left, k, curr, kth);
    ++curr;
    if(curr == k) {
      kth = root->val;
      return;
    }
    getKth(root->right, k, curr, kth);
  }

  int kthSmallest(TreeNode* root, int k) {
    // Do an in-order path, the k-th visited element is what we want
    int curr = 0;
    int kth;
    getKth(root, k, curr, kth);
    return kth;
  }
};

int main()
{
  cout << "Hello, World!";
  return 0;
}