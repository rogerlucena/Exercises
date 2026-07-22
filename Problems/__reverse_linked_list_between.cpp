#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://neetcode.io/problems/reverse-linked-list-ii
// https://leetcode.com/problems/reverse-linked-list-ii
// https://www.interviewbit.com/problems/reverse-link-list-ii
// Remember: if the head may be modified (moved, deleted etc) or you do not know yet who will be the head in answer -> consider using a sentinel,
// also if you start using too much "ifs" to handle the head (or left = 1 here) differently that is another sign that you should consider a sentinel.
// The best is the behavior of the code to flow and be the same for all nodes including head (if it is not the current case -> sign to consider sentinel). More tips for identifying when to use a sentinel in __copy_linked_list_with_random_pointer.cpp
// Also, have how to reverse a linked list in-place remembered by heart.

// Reverse a linked list from position left to right (1-indexed). Do it in-place and in one-pass.
// For example:
// Given 1->2->3->4->5->NULL, left = 2 and right = 4,
// return 1->4->3->2->5->NULL.

// - Note:
// Given left, right satisfy the following condition:
// 1 ≤ left ≤ right ≤ length of list.
// - Note 2:
// Usually the version often seen in the interviews is reversing the whole linked list which is obviously an easier version of this question.

ListNode* reverseBetween(ListNode* head, int left, int right) {
	ListNode dummy(0, head);

	// aux->next should point to the first node to be reversed.
	ListNode* aux = &dummy;
	for (int i = 1; i < left; ++i) {
		aux = aux->next;
	}

	ListNode* prev = nullptr;
	ListNode* curr = aux->next;
	ListNode* next = nullptr;
	for (int i = 1; i <= right - left + 1; ++i) {  // remember to keep the +1 here.
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	aux->next->next = curr;
	aux->next = prev;

	return dummy.next;
}

int main() {
	vector<int> v = {1, 2, 3, 4, 5};
	ListNode* head = generateList(v);
	int left = 2;
	int right = 4;

	printList(head);
	head = reverseBetween(head, left, right);
	printList(head);

	return 0;
}