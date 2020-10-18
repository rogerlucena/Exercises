#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/swap-list-nodes-in-pairs/
// https://leetcode.com/problems/swap-nodes-in-pairs/
// Swap nodes in pairs
// Idea of the sentinel node, linked lists manipulation (attention with infinite loops and null access in while below)
// (the head of the list may be changed - sentinel idea interesting here)

// Given a linked list, swap every two adjacent nodes and return its head.
// You may not modify the values in the list's nodes, only nodes itself may be changed.
// Example:
// Given 1->2->3->4, you should return the list as 2->1->4->3.

ListNode* swapTwo(ListNode* h) {
	ListNode* tmp = h->next;
	h->next = h->next->next;
	tmp->next = h;
	return tmp;
}

ListNode* mySwapPairs(ListNode* head) {
	ListNode ans(-1);
	ans.next = head;
	ListNode* prev = &ans;
	while(prev->next && prev->next->next) {
		prev->next = swapTwo(prev->next);
		prev = prev->next->next;
	}

	return ans.next;
}

ListNode* swapPairs(ListNode* head) {
	if(!head) {
		return head;
	}

	ListNode ans(0);
	ans.next = head;
	ListNode* aux = &ans;

	while(aux->next && aux->next->next) {
		ListNode* curr = aux->next;
		ListNode* rest = aux->next->next->next;

		aux->next = curr->next;
		curr->next->next = curr;
		curr->next = rest;

		aux = aux->next->next;
	}

	return ans.next;
}

int main() {
	vector<int> v = {1, 2, 3, 4, 5};
	ListNode* l = generateList(v);
	printList(l);
	printList(swapPairs(l));

	return 0;
}