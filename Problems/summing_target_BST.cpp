#include <iostream>

using namespace std;

/*
    Given a BST, search if there are 2 numbers summing to a target:

    https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/
*/

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x, TreeNode* l = NULL, TreeNode* r = NULL) : val(x), left(l), right(r) {}
};

class Solution {
 public:
  TreeNode* originalRoot;

  bool thereIs(TreeNode* root, int el, TreeNode* diffOf) {
      if(root == NULL)
          return false;
      if(root->val == el && root != diffOf)
          return true;
      else if(el < root->val)
          return thereIs(root->left, el, diffOf);
      else return thereIs(root->right, el, diffOf);
  }

  bool findTarget2(TreeNode* root, int target) {
      if(root == NULL)
          return false;

      int complement = target - root->val;
      bool got = false;
      if(complement < root->val)
          got = thereIs(originalRoot, complement, root);
      else got = thereIs(originalRoot, complement, root);
      if(got)
          return true;
      else
          return findTarget2(root->left, target) || findTarget2(root->right, target);
  }

  bool findTarget(TreeNode* root, int target) {
    originalRoot = root;

    return findTarget2(root, target);
  }
};

int main()
{
//    TreeNode t4 (4);
//    TreeNode t2 (2);
//    TreeNode t3 (3, &t2, &t4);
//    TreeNode t7 (7);
//    TreeNode t6 (6, NULL, &t7);
//    TreeNode t5 (5, &t3, &t6);

    TreeNode t1 (1);
    TreeNode t3 (3);
    TreeNode t2 (2, &t1, &t3);

    Solution sol;
    cout << sol.findTarget(&t2, 4) << endl;

    return 0;
}