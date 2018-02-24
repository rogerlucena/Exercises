#include <iostream>

using namespace std;

/*

 Two number are represented in linked lists, sum them.

 https://leetcode.com/problems/add-two-numbers/description/

*/

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
  ListNode(int x, ListNode &n) : val(x), next(&n) {}
};

class Solution {
 public:

  void add1(ListNode* l) {
    l->val += 1;
    if(l->val < 10)
      return;
    else{
      l->val -= 10;
      if(l->next == NULL)
        l->next = new ListNode(1);
      else add1(l->next);
    }
  }

  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* sol = new ListNode(0);
    if(l1 == NULL && l2 == NULL) {
      return NULL;
    }
    else if(l1 == NULL) {
      sol = l2;
    }
    else if(l2 == NULL) {
      sol = l1;
    }
    else {
      //cout << "l1: " << l1->val << " l2: " << l2->val << endl;
      ListNode sol2 (l1->val+l2->val);
      if(sol2.val >= 10) {
        sol2.val -= 10;
        if(l1->next == NULL) {
          l1->next = new ListNode(1);
        }
        else {
          add1(l1->next);
        }
      }

      sol->val = sol2.val;
      sol->next = addTwoNumbers(l1->next, l2->next);
    }

    return sol;
  }
};

int main() {
  ListNode l_3 (3);
  ListNode l_4 (4, l_3);
  ListNode l1 (2, l_4);

  ListNode l_4_(4);
  ListNode l_6 (6, l_4_);
  ListNode l2 (5, l_6);

  Solution sol;

  ListNode* ans = sol.addTwoNumbers(&l1, &l2);
  while(ans != NULL) {
    cout << ans->val << endl;
    ans = ans->next;
  }

  return 0;
}