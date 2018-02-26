#include <iostream>

using namespace std;

/*
  Find the intersection between two linked lists:

  https://leetcode.com/explore/interview/card/top-interview-questions-medium/107/linked-list/785/

*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
 public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    int l1, l2;
    l1 = l2 = 0;

    ListNode* aux = headA;
    while (aux != NULL) {
      ++l1;
      aux = aux->next;
    }

    aux = headB;
    while (aux != NULL) {
      ++l2;
      aux = aux->next;
    }

    int d = abs(l1-l2);
    ListNode *a, *b;
    a = headA;
    b = headB;

    if(l1>l2) {
      while (d>=1) {
        a = a->next;
        --d;
      }
    }
    else {
      while (d>=1) {
        b = b->next;
        --d;
      }
    }

    while (a != b) {
      a = a->next;
      b = b->next;
    }

    return a;
  }
};

int main()
{
  cout << "Hello, World!";
  return 0;
}