#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/remove-nth-node-from-end-of-list/
// Review: remember to use sentinel "dummy" for corner cases (eg: only one node), clever idea to use two pointers and put a space of "n" nodes between them at the beginning.

// Given the head of a linked list, remove the nth node from the end of the list and return its head.
// Follow up: Could you do this in one pass?

// Solution in one pass: use two pointers, and at the beginning advance one of them in n steps (the number of nodes between the pointers will be "n" then as wanted).
// Remember sentinel "dummy" for corner cases here (only one node). 
ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode dummy;
	dummy.next = head;
	
	ListNode* fst = &dummy;
	ListNode* scnd = head;
	for(int i = 1; i <= n; ++i) {
		scnd = scnd->next;
	}

	while(scnd) {
		scnd = scnd->next;
		fst = fst->next;
	}
	fst->next = fst->next->next;

	return dummy.next;
}

int main() {
	cout << "Hello, World!";
	return 0;
}