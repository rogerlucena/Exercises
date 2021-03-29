#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/partition-list/

// Given the head of a linked list and a value x, partition it such that all nodes less than x come before
// nodes greater than or equal to x.

// You should preserve the original relative order of the nodes in each of the two partitions.

ListNode* partition(ListNode* head, int x) {
	ListNode* hSentinel = new ListNode();
	hSentinel->next = head;
	ListNode* prev = hSentinel;
	
	ListNode* other = new ListNode();
	ListNode* curr = other;
	for (; prev->next;) {
		if (prev->next->val >= x) {
			curr->next = prev->next;
			prev->next = prev->next->next;
			curr = curr->next;
			curr->next = nullptr;
		} else {
			prev = prev->next;
		}
	}

	prev->next = other->next;
	return hSentinel->next;
}

int main() {
	ListNode* head = generateList({1,4,3,2,5,2}); // ans: [1,2,2,4,3,5]
	int x = 3;
	ListNode* ans = partition(head, x);
	printList(ans);
	
	return 0;
}