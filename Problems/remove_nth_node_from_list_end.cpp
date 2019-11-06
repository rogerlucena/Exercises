#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/remove-nth-node-from-list-end/

// Given a linked list, remove the nth node from the end of list and return its head.

// For example,
// Given linked list: 1->2->3->4->5, and n = 2.
// After removing the second node from the end, the linked list becomes 1->2->3->5.

// Note:
// If n is greater than the size of the list, remove the first node of the list.

ListNode* removeNthFromEnd(ListNode* A, int B) {
	int listSize = 0;
	ListNode* aux = A;
	while(aux != nullptr) {
		++listSize;
		aux = aux->next;
	} 
	if(B >= listSize) {
		return A->next;
	}

	aux = A;
	for(int i = 1; i < (listSize - B); ++i) {
		aux = aux->next;
	}

	ListNode* tmp = aux->next;
	aux->next = tmp->next;
	tmp->next = nullptr;
	delete tmp;

	return A;
}

int main() {
	vector<int> v = {1, 2, 3, 4, 5};
	ListNode* A = generateList(v);
	int B = 2;
	printList(A);
	A = removeNthFromEnd(A, B);
	printList(A);

	return 0;
}