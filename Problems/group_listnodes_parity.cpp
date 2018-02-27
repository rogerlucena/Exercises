#include <iostream>

using namespace std;

/*
  Given a linked list, group all odd nodes (indexes) together followed by the even nodes.

  https://leetcode.com/explore/interview/card/top-interview-questions-medium/107/linked-list/784/
*/

// Definition for singly-linked list.
struct Node {
    int val;
    Node *next;
    Node(int v, Node* n = NULL) : val(v), next(n) {}
    void print() {
      cout << val << " ";
      Node* tmp = next;
      while (tmp != NULL) {
        cout << tmp->val << " ";
        tmp = tmp->next;
      }
      cout << endl;
    }
};

class Solution {
 public:
  Node* oddEvenList(Node* h) {
    if (h == NULL || h->next == NULL) { // stop condition for lists with a pair size (even number of nodes)
      return h;
    }
    Node *oInit, *pInit, *o, *p; // begining of odd and pair sublists, and their auxiliar pointers
    oInit = o = h;
    pInit = p = h->next;

    while (true) {
      if (p->next == NULL) {
        o->next = pInit;
        break;
      }
      o->next = o->next->next; // separating the sublists
      p->next = p->next->next;

      o = o->next; // iterative step
      p = p->next;

      if (p == NULL) { // stop condition for lists with an odd size
        o->next = pInit;
        break;
      }
    }

    return oInit;
  }
};

int main() {
  Node* l = new Node(1, new Node(2, new Node(3, new Node(4, new Node(5)))));
  cout << "Original list:" << endl;
  l->print();
  cout << "New list:" << endl;
  Solution sol;
  sol.oddEvenList(l)->print();

  return 0;
}