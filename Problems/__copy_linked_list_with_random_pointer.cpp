#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// https://neetcode.io/problems/copy-linked-list-with-random-pointer
// https://leetcode.com/problems/copy-list-with-random-pointer
// Remember: C++ already has a built-in hash function for any type of pointers <T*> (it is just a memory address in the form of a 32-bit or 64-bit unsigned integer, see remember_hash_map.cpp for example, or below).
// Common problem for senior and staff/principal SWE interviews (founder of Neetcode commented in podcast).
// Remember: [] for hash maps changes the map and insert default value for a key if that key does not previously exist in the map (0 for int, nullptr for <T*>), it is then not allowed
// when the map is const - in that case use the method .at() (which gives an error if the asked key does not exist).
// Remember: nice shortcuts to understand if you need a sentinel node to answer a Linked List problem (as with dummy in the 2nd solution below):
// 1) Am I Changing the Head? = Is there a chance that the head node of the returned list will be different from the head node of the input list? -> eg: Deletion, Insertion/Merging, Partitioning/Rearranging (Moving nodes around);
// 2) Look for the "Previous Node" Dependency: If you need a prev pointer initialized to something valid so that your loop logic works uniformly from index 0 to index N, use a sentinel -> eg: To delete a node, you write prev->next = curr->next. If curr is the very first node, prev is nullptr ...;
// 3) The "Uniform Loop" Test: Can I use the exact same code logic for the 1st node as I do for the 5th node? - avoid if (isFirstNode) checks (if you think about it consider using a sentinel to avoid the messy code you would be about to write) - this is the hint for the case below using dummy.
// Hint: Attempt to sketch the solution assuming a sentinel/dummy node exists. If you find that your loop starts smoothly **without any if (head == nullptr) or if (isFirstNode) checks**, keep it. You will quickly realize that about 80% of structural linked list problems become cleaner with a sentinel node. It costs O(1) memory and saves you 20 lines of bug-prone edge-case code.

// Problem description:

// You are given the head of a linked list of length n. Unlike a singly linked list, each node contains an additional pointer
// random, which may point to any node in the list, or null.
// Create a deep copy of the list.
// The deep copy should consist of exactly n new nodes, each including:

// The original value val of the copied node
// A next pointer to the new node corresponding to the next pointer of the original node
// A random pointer to the new node corresponding to the random pointer of the original node
// Note: None of the pointers in the new list should point to nodes in the original list.

// Return the head of the copied linked list.

// In the examples, the linked list is represented as a list of n nodes. Each node is represented as a pair of 
// [val, random_index] where random_index is the index of the node (0-indexed) that the random pointer points to, or null if it
// does not point to any node.

// Example:
// Input: head = [[3,null],[7,3],[4,0],[5,1]]
// Output: [[3,null],[7,3],[4,0],[5,1]]

// Constraints:
// 0 <= n <= 100
// -100 <= Node.val <= 100
// Node values are not guaranteed to be unique.
// random is null or is pointing to some node in the linked list.

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

// Easier (but not optimal in space) solution with Hash Map: O(n) in time and O(n) in space.
Node* copyRandomList(Node* head) {
	unordered_map<Node*, Node*> old_to_new;

	Node* curr = head;
	while (curr) {
		Node* new_node = new Node(curr->val);
		old_to_new[curr] = new_node;
		curr = curr->next;
	}

	curr = head;
	while (curr) {
		Node* new_node = old_to_new[curr];
		new_node->next = old_to_new[curr->next];
		new_node->random = old_to_new[curr->random];  // if curr->random = nullptr, creates a nullptr key in the hash map and sets its value to the default value for that type = nullptr as we wanted (same for when curr->next is mullptr above).
		curr = curr->next;
	}

	return old_to_new[head];
}
// As a senior SWE also comment: "Object Ownership & Memory Leaks - In a real production environment, returning a raw pointer (Node*) is
// an anti-pattern because it creates ambiguity around ownership (who is responsible for deleteing this memory?). A senior engineer should
// note: 'In production code, I would look to wrap this graph/list structure in std::shared_ptr or manage lifetime via a custom RAII container
// class to prevent memory leaks'", and also mention that the hash map already works for pointers as key too (built-in hash function for any type of pointers).
// Edge Cases Handled:
// a) head is null.
// b) a node’s random pointer points to itself (loop).
// c) all random pointers are null.


// Optimized solution from Neetcode (more prone to errors during the live interview, but show more seniority):
// The Interweaving Method - O(n) in time and O(1) in space.
// Steps:
// 1) Iterate and Clone (Interweave): Create a copy of each node and insert it immediately after its original node (using the original list to simulate the hash map itself).
// 2) Copy Random Pointers
// 3) Separate the Lists to isolate the deep copy.
Node* copyRandomList(Node* head) {
	if (!head) {
		return nullptr;
	}

	// Step 1: Interweave original nodes with new copied nodes.
	Node* curr = head;
	while (curr) {
		Node* copy_node = new Node(curr->val);
		copy_node->next = curr->next;
		
		Node* next_node = curr->next;
		curr->next = copy_node;		
		curr = next_node;
	}

	// Step 2: Assign random pointers for the copied nodes.
	curr = head;
	while (curr) {
		if (curr->random != nullptr) {
			curr->next->random = curr->random->next;  // the copy of that random is just ->next to it (simulating a hash map inside the original list itself).
		}
		// Move to the next original node.
		curr = curr->next->next; 
	}

	// Step 3: Separate the original and copied lists.
	curr = head;
	Node dummy(0);
	Node* copy_curr = &dummy;  // the curr of the copied list.
	while (curr) {
		// Extract the copy.
		copy_curr->next = curr->next;
		copy_curr = copy_curr->next;  // the next position to insert the next copied node.

		// Restore the original list.
		curr->next = curr->next->next;
		curr = curr->next;
	}

	return dummy.next;
}
// Senior SWE should comment: 1) "Modifying the Input: In the O(1) space solution, you temporarily mutate the user's input list.
// A great senior candidate will call this out: 'In a production environment, if this structure is accessed across multiple threads,
// mutating the input in place could introduce race conditions unless properly locked.'"
// And: 2) "Stack vs. Heap Allocation: Notice the use of Node dummy(0); in the unweaving step of Approach 1. Creating the dummy node on
// the stack instead of the heap (new Node(0)) avoids an unnecessary heap allocation and ensures it is automatically destroyed when the
// function goes out of scope, eliminating a potential memory leak."

int main() {
	cout << "Hello, World!";
	return 0;
}