#include <iostream>
#include <vector>
#include <queue>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/merge-k-sorted-lists/
// min heap with custom cmp to store the smaller, sentinel idea again

// Merge k sorted linked lists and return it as one sorted list.

// Example:
// 1 -> 10 -> 20
// 4 -> 11 -> 13
// 3 -> 8 -> 9
// will result in
// 1 -> 3 -> 4 -> 8 -> 9 -> 10 -> 11 -> 13 -> 20

ListNode* mergeKLists(vector<ListNode*> &A) {
	auto cmp = [](const ListNode* a, const ListNode* b) -> bool {return a->val > b->val;};
	priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp, A); // O(k) in time, Floyd's algorithm
	
	ListNode ans(-1); // The destructor could delete ans.next? Yes (end of scope) We do not want that, works here because no destructor
	ListNode* tmp = &ans;

	while(!q.empty()) {
		ListNode* next = q.top();
		q.pop(); // O(log k) in time

		tmp->next = next;
		next = next->next;
		if(next) {
			q.push(next); // O(log k) in time
		}
		tmp = tmp->next;
	}

	return ans.next;
}

int main() {
	ListNode* l1 = generateList({1, 10, 20});
	ListNode* l2 = generateList({4, 11, 13});
	ListNode* l3 = generateList({3, 8, 9});

	vector<ListNode*> A = {l1, l2, l3};
	printList(mergeKLists(A));

	return 0;
}