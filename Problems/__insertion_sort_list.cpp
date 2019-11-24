#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/insertion-sort-list/

// Sort a linked list using insertion sort.
// Example :
// Input : 1 -> 3 -> 2
// Return 1 -> 2 -> 3

// Rewriting website solution:
// Initialize a pointer "sorted" as nullptr, go through the original list with "curr",
// if sorted is null or its first element is greater than "curr", add "curr" at the beginning of "sorted"
// else add curr somewhere after the first element of "sorted"
ListNode* insertionSortList(ListNode* A) {
	if(A == nullptr || A->next == nullptr) {
		return A;
	}

	ListNode* list = A;
	ListNode* sorted = nullptr;

	while (list) {
		ListNode* curr = list;
		list = list->next;

		if(sorted == nullptr || sorted->val > curr->val) { // add "curr" at the beginning of "sorted"
			curr->next = sorted;
			sorted = curr;
		} else { // add "curr" somewhere after the fist element of "sorted"
			ListNode* s = sorted;
			while(s) {
				ListNode* prev = s;
				s = s->next;
				if(prev->next == nullptr || prev->next->val > curr->val) { // add "curr" after "prev" in "sorted"
					curr->next = prev->next;
					prev->next = curr;
					break;
				}
			}
		}
	}

	return sorted;
}

ListNode* reverseList(ListNode* A) {
	ListNode* prev = nullptr;
	ListNode* curr = A;
	ListNode* next = nullptr;

	while(curr != nullptr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	A = prev;

	return A;
}

ListNode* advancePositions(ListNode* A, int n) {
	if(n == -1) {
		ListNode* sentinel = new ListNode(-1);
		sentinel->next = A;
		return sentinel;
	}

	for(int i = 1; i <= n; ++i) {
		A = A->next;
	}

	return A;
}

ListNode* oldInsertionSortList(ListNode* A) {
    if(A == nullptr || A->next == nullptr ) {
		return A;
	}

	ListNode* aux = A;
	int size = 0; 
	while(aux != nullptr) {
		++size;
		aux = aux->next;
	}
	aux = A;

	for(int i = 1; i <= size-1; ++i) {
		ListNode* prev = advancePositions(aux, (size-1)-1-i);
		int key = prev->next->val;

		ListNode* pos = prev->next;
		while(pos->next != nullptr && pos->next->val > key) {
			pos = pos->next;
		}

		// Insert node with "key" value just after position "pos"
		if(pos != prev->next) {
			ListNode* curr = prev->next; // our key node
			prev->next = prev->next->next; // we jump our "key" node ("curr")
			ListNode* posNext = pos->next;
			pos->next = curr; // we add our "key" node ("curr")
			curr->next = posNext;
		}

		if(i == size-1) {
			A = prev->next;
			prev->next = nullptr;
			delete prev;
		}
	}

	A = reverseList(A);
	return A;
}

int main() {
	vector<int> v = {1, 3, 2};
	ListNode* A = generateList(v);
	printList(A);
	A = insertionSortList(A);
	printList(A);

	return 0;
}