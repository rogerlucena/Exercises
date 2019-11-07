#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/sort-list/

// Sort a linked list in O(n log n) time using constant space complexity.

ListNode* merge(ListNode* a, ListNode* b) {
	ListNode ans(-1);
	ListNode* tmp = &ans;

	while(a && b) {
		if(a->val <= b->val) {
			tmp->next = a;
			a = a->next;
		} else {
			tmp->next = b;
			b = b->next;
		}
		tmp = tmp->next;
	}
	if(a) {
		tmp->next = a;
	} else {
		tmp->next = b;
	}

	return ans.next;
}

ListNode* sortList(ListNode* A) {
	if(A == nullptr || A->next == nullptr) {
		return A;
	}

	int size = 0;
	ListNode* l = A;
	while(l) {
		++size;
		l = l->next;
	}
	l = A;

	ListNode* mid = l;
	for(int i = 0; i < size/2-1; ++i) {
		mid = mid->next;
	}

	// Set an end for the first half of the list
	ListNode* tmp = mid->next;
	mid->next = nullptr;
	mid = tmp;

	l = sortList(l);
	mid = sortList(mid);

	// Merge the two list together
	A = merge(l, mid);

	return A;
}

ListNode* recursiveMerge(ListNode* a, ListNode* b) {
	if(!a) {
		return b;
	} else if(!b) {
		return a;
	}

	ListNode* result = nullptr;

	if(a->val <= b->val) {
		result = a;
		result->next = recursiveMerge(a->next, b);
	} else {
		result = b;
		result->next = recursiveMerge(a, b->next);
	}

	return result;
}

int main() {
	vector<int> v = {1, 5, 4, 3};
	ListNode* A = generateList(v);
	printList(A);
	A = sortList(A);
	printList(A);

	// ListNode* l1 = generateList({1, 3});
	// ListNode* l2 = generateList({2, 4});
	// printList(merge(l1, l2));

	return 0;
}