#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/reverse-link-list-ii/

// Reverse a linked list from position m to n. Do it in-place and in one-pass.
// For example:
// Given 1->2->3->4->5->NULL, m = 2 and n = 4,
// return 1->4->3->2->5->NULL.

// - Note:
// Given m, n satisfy the following condition:
// 1 ≤ m ≤ n ≤ length of list.
// - Note 2:
// Usually the version often seen in the interviews is reversing the whole linked list which is obviously an easier version of this question. 

ListNode* reverseBetween(ListNode* A, int B, int C) {
	ListNode* aux = A;
	if(B == 1) {
		aux = new ListNode(-1);
		aux->next = A;
	} else {
		for(int i = 1; i <= B-2; ++i) {
			aux = aux->next;
		}
	}

	ListNode* prev = nullptr;
	ListNode* curr = aux->next;
	ListNode* next = curr;

	for(int i = 0; i <= C-B; ++i) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	aux->next->next = curr;
	aux->next = prev;

	if(B==1) {
		return prev;
	} else {
		return A;
	}
}

int main() {
	vector<int> v = {1, 2, 3, 4, 5};
	ListNode* A = generateList(v);
	int B = 2;
	int C = 4;

	printList(A);
	A = reverseBetween(A, B, C);
	printList(A);

	return 0;
}