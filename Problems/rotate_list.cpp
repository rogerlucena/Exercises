#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/rotate-list/

// Given a list, rotate the list to the right by k places, where k is non-negative.

// For example:
// Given 1->2->3->4->5->NULL and k = 2,
// return 4->5->1->2->3->NULL.

ListNode* rotateRight(ListNode* A, int B) {
	if(!A || !A->next) {
		return A;
	}

	int size = 0;
	ListNode* curr = A;
	ListNode* last = nullptr;
	while(curr) {
		if(curr->next == nullptr) {
			last = curr;
		}
		++size;
		curr = curr->next;
	}

	B = B % size;
	if(B == 0) {
		return A;
	}

	curr = A;
	ListNode* prev = nullptr;
	for(int i = 1; i <= size - B; ++i) {
		prev = curr;
		curr = curr->next;
	}
	// curr always pointing to the first node of the new list to be returned
	ListNode ans(-1);
	ans.next = A;
	if(prev) {
		ans.next = curr;
		prev->next = nullptr;
		last->next = A;
	}

	return ans.next;
}

int main() {
	cout << "Hello, World!";
	return 0;
}