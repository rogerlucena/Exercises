// C program to merge a linked list into another at
// alternate positions
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;


// Important routines for linked lists to know by heart:
// - Inverse a linked list in place
// - Merge two linked lists (alternating positions)

// std::list -> is a doubly linked list (can operate with pointers, different than deque - see lru_cache problem)
// .front(), .back(), .clear(), push_back, push_front, pop_back, pop_front
//      void remove (const value_type& val); -> remove elemnts with that value
//      iterator erase (iterator position);
//      iterator erase (iterator first, iterator last);
//          erase return an iterator to the the element that followed the last element erased by the function call             
//      iterator insert (iterator position, const value_type& val);
//      void insert     (iterator position, size_type n, const value_type& val) // n repetitions of val
//      void insert     (iterator position, InputIterator first, InputIterator last)
//          add just before "position" and return an "it" to the first of the newly added elements (first case)
//          (same thing with std::deques)


// Reverse in-place a linked list
// https://www.geeksforgeeks.org/reverse-a-linked-list/
ListNode* reverseList(ListNode* h) {
	ListNode* prev = nullptr;
	ListNode* curr = h;
	ListNode* next = nullptr;

	while(curr != nullptr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}	
	h = prev;

	return h;
}

// Merge two sorted lists
ListNode* mergeSorted(ListNode* a, ListNode* b) {
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

// --- Old code:

// Another way - reversing lists
ListNode* inverse(ListNode *root) {
    ListNode* res = new ListNode(-1); // good strategy, "cabeça" node, not necessary here, but good
    while (root != NULL) {
        ListNode* temp = root->next; // saving the rest of the list
        root->next = res->next; //
        res->next = root;
        root = temp;
    }

    return res->next;
}

/* Function to insert a node at the beginning */
void push(ListNode ** head_ref, int new_data) {
    ListNode* new_node = new ListNode(-1);
    new_node->val  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)  = new_node;
}

// Main function that inserts nodes of linked list q into p at
// alternate positions. Since head of first list never changes
// and head of second list  may change, we need single pointer
// for first list and double pointer for second list.
void merge(ListNode *p, ListNode **q) {
    ListNode *p_curr = p, *q_curr = *q;
    ListNode *p_next, *q_next;

    // While there are available positions in p
    while (p_curr != NULL && q_curr != NULL) {
        // Save next pointers
        p_next = p_curr->next;
        q_next = q_curr->next;

        // Make q_curr as next of p_curr
        q_curr->next = p_next;  // Change next pointer of q_curr
        p_curr->next = q_curr;  // Change next pointer of p_curr

        // Update current pointers for next iteration
        p_curr = p_next;
        q_curr = q_next;
    }

    *q = q_curr; // Update head pointer of second list
}

// Driver program to test above functions
int main() {
    ListNode *p = NULL, *q = NULL;
    push(&p, 3);
    push(&p, 2);
    push(&p, 1);
    printf("First Linked List:\n");
    printList(p);

    push(&q, 8);
    push(&q, 7);
    push(&q, 6);
    push(&q, 5);
    push(&q, 4);
    printf("Second Linked List:\n");
    printList(q);

    merge(p, &q);

    printf("Modified First Linked List:\n");
    printList(p);
    printList(q);
    
    cout << "Modified Second Linked List:" << endl;
    printList(q);

    // Testing inverse method:
    cout << endl << "Testing inverse method" << endl;
    cout << "Original list:" << endl;
    vector<int> v = {1, 2, 3, 4, 5};
	ListNode* h = generateList(v);
    printList(h);

    cout << "Inversed list:" << endl;
    h = reverseList(h);
    printList(h);
    cout << endl;

    cout << "Merging lists:" << endl;
    ListNode* l1 = generateList({1, 3});
	ListNode* l2 = generateList({2, 4});
	printList(mergeSorted(l1, l2));

    return 0;
}