#include <iostream>
#include <vector>
#include <math.h>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/subtract/

// Given a singly linked list, modify the value of first half nodes such that :
// 1st node’s new value = the last node’s value - first node’s current value
// 2nd node’s new value = the second last node’s value - 2nd node’s current value,
// and so on …

// Example :
// Given linked list 1 -> 2 -> 3 -> 4 -> 5,
// You should return 4 -> 2 -> 3 -> 4 -> 5

ListNode* reverseFrom(ListNode* a, int s) { // [s, end], start included (indexed from 1) till the end
	for(int i = 1; i < s; ++i) {
		a = a->next;
	}

	ListNode* prev = nullptr;
	ListNode* curr = a;
	ListNode* next = nullptr;

	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	a = prev;

	return a;
}

int getSize(ListNode* a) {
	int size = 0;
	while(a) {
		++size;
		a = a->next;
	}
	return size;
}

ListNode* subtract(ListNode* A) {
	if(A == nullptr || A->next == nullptr) {
		return A;
	}

	int size = getSize(A);
	int halfSize = floor(size/2);

	ListNode* secondHalfReversed = reverseFrom(A, halfSize+1);
	ListNode* l2 = secondHalfReversed;

	ListNode* l1 = A;
	for(int i = 0; i < halfSize; ++i) {
		l1->val = l2->val - l1->val;
		l1 = l1->next;
		l2 = l2->next;
	}

	reverseFrom(secondHalfReversed, 1);

	return A;
}

int main() {
	vector<int> v = {1, 2, 3, 4, 5};
	ListNode* A = generateList(v);
	printList(A);
	A = subtract(A);
	printList(A);
	
	return 0;
}