#include <iostream>
#include <vector>
#include "tools.cpp"

using namespace std;

// https://neetcode.io/problems/reorder-linked-list
// https://leetcode.com/problems/reorder-list
// Review: nice to review reverse in place and fast and slow pointers to get the end of the first half.

// You are given the head of a singly linked-list.
// The positions of a linked list of length = 7 for example, can intially be represented as:
// [0, 1, 2, 3, 4, 5, 6]
// Reorder the nodes of the linked list to be in the following order:
// [0, 6, 1, 5, 2, 4, 3]

// Notice that in the general case for a list of length = n the nodes are reordered to be in the following order:
// [0, n-1, 1, n-2, 2, n-3, ...]
// You may not modify the values in the list's nodes, but instead you must reorder the nodes themselves.

// Example 1:
// Input: head = [2,4,6,8]
// Output: [2,8,4,6]

// Example 2:
// Input: head = [2,4,6,8,10]
// Output: [2,10,4,8,6]

// Constraints:
// 1 <= Length of the list <= 1000.
// 1 <= Node.val <= 1000


// Fast and slow pointers (the middle node stays in the first half if odd number of nodes).
// (useful to check for a cycle in the linked list as well for other problems)
ListNode* getEndOfirstHalf(ListNode* head) {
	if (!head) {
		return head;
	}
	
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

// Reverse in-place.
ListNode* reverseLinkedList(ListNode* head) {
	ListNode* prev = nullptr;
	ListNode* curr = head;
	ListNode* next = nullptr;

	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	
	return prev;
}

void reorderList(ListNode* head) {
	ListNode* enf_of_first_half = getEndOfirstHalf(head);
	
	ListNode* second_half = enf_of_first_half->next;
	enf_of_first_half->next = nullptr;

	ListNode* reversed_second_half = reverseLinkedList(second_half);

	ListNode* l1 = head;
	ListNode* l2 = reversed_second_half;
	while (l1 && l2) {
		ListNode* l1_next = l1->next;
		l1->next = l2;
		ListNode* l2_next = l2->next;
		l2->next = l1_next;
		l1 = l1_next;
		l2 = l2_next;
	}
}

int main() {
	cout << "Hello, World!";
	return 0;
}