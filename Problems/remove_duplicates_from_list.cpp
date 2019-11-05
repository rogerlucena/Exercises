#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/remove-duplicates-from-sorted-list/

// Given a sorted linked list, delete all duplicates such that each element appear only once.

// For example,
// Given 1->1->2->3->3, return 1->2->3.

ListNode* deleteDuplicates(ListNode* A) {
	if(A == nullptr) {
		return A;
	}

	ListNode* prev = A;
	ListNode* curr = A->next;

	while(curr != nullptr) {
		if(curr->val == prev->val) {
			prev->next = curr->next;
			curr = curr->next;
		} else {
			prev = curr;
			curr = curr->next;
		}
	}

	return A;
}


int main() {
	vector<int> v = {1, 1, 2, 3, 3};
	ListNode* h = generateList(v);
	printList(h);
	h = deleteDuplicates(h);
	printList(h);

	return 0;
}