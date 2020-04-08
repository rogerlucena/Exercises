#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/middle-of-the-linked-list/

// Given a non-empty, singly linked list with head node head, return a middle node of linked list.
// If there are two middle nodes, return the second middle node.

ListNode* middleNode(ListNode* head) {
    int size = 0;
	for(ListNode* n = head; n; n = n->next) {
		++size;
	}

	ListNode* middle = head;
	for(int i = 1; i <= size/2; ++i) {
		middle = middle->next;
	}

	return middle;
}

int main() {
	cout << "Hello, World!";
	return 0;
}