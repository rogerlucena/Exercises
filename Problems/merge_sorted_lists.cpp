#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

ListNode* mergeTwoLists(ListNode* A, ListNode* B) {
	ListNode ans(-1);
	ListNode* tmp = &ans;

	while(A && B) {
		if(A->val <= B->val) {
			tmp->next = A;
			A = A->next;
		} else {
			tmp->next = B;
			B = B->next;
		}
		tmp = tmp->next;
	}
	if(A) {
		tmp->next = A;
	} else {
		tmp->next = B;
	}

	return ans.next;
}

int main() {
	vector<int> v1 = {1, 3, 5, 6};
	vector<int> v2 = {2, 4};
	ListNode* l1 = generateList(v1);
	ListNode* l2 = generateList(v2);
	printList(mergeTwoLists(l1, l2));

	return 0;
}