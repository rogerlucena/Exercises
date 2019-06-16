#include <iostream>

#include<vector>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
*/

// Swap nodes in pairs
// https://leetcode.com/problems/swap-nodes-in-pairs/

// Given a linked list, swap every two adjacent nodes and return its head.
// You may not modify the values in the list's nodes, only nodes itself may be changed.
// Example:
// Given 1->2->3->4, you should return the list as 2->1->4->3.

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

void printList(ListNode* head) {
    ListNode* it = head;
    while (it != NULL) {
      cout << it->val << " ";
      it = it->next;
    }
    cout << endl;
}

ListNode* swapFirstTwo(ListNode* r) {
  if(r->next->next == NULL) {
    return r;
  }
  // cout << "Start of swapFirstTwo" << endl; 
  ListNode* tmp = head->next;
  // cout << "head: ";
  // printList(head);
  head->next = tmp->next;
  tmp->next = head;
  head = tmp;
  // cout << "head: ";
  // printList(head);
  // cout << "End of swapFirstTwo" << endl; 
  return head;
}

ListNode* swapPairs(ListNode* head) {
    ListNode* it = new ListNode(-1);
    it->next = head;
    int c = 0;
    while (it->next != NULL) {
      // Go changing between 0 and 1
      // (Create a function to take h and swap two and return)
      // if(0) 
      //   Use the swap2 function
      // cout << "In swapPairs, head1: ";
      // printList(head);
      if(c%2 == 0) {
        it = swapFirstTwo(it);
      } 
      c++;
      // cout << "In swapPairs, head2: ";
      // printList(head);
      it = it->next;
    }
    // cout << "Answer of swapPairs: ";
    // printList(head);
    return head;
}

ListNode* createListNode(vector<int>& v) {
  if(v.size() == 0) {
    return NULL;
  }
  ListNode* ans = new ListNode(v[0]);
  ListNode* it = ans;
  for(int i=1; i<v.size(); i++) {
    it->next = new ListNode(v[i]);
    it = it->next;
  }

  return ans;
}

int main() {
    vector<int> v = {1, 2}; // {1, 2, 3, 4, 5, 13, 8}
    ListNode* h = createListNode(v);
    printList(h);
    printList(swapPairs(h));
    cout << "Program finished.";
}