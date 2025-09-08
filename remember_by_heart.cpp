#include <iostream>
#include <vector>
#include <queue>

#include "tools.cpp"

using namespace std;

// Also:
// sort a linked list? (merge sort)
// quick sort?

// Remember: If "v" is an empty vector -> v.size()-1: 18446744073709551615 
// Attention when iterating a vector backwards, in the edge case of empty input you can be in trouble! 
// 			- treat this edge case separated (maybe along with v.size() == 1) at the beginning! 


// DFS:
void dfs(v, &visited) {
	doSomething(v);
	visited[v] = true;
	for(neigh : neighbors(v)) {
		if(!visited[neigh]) {
			dfs(neigh, visited);
		}
	}
}

// Iterative DFS (but prefer the recursive one - simpler).
// (difference is that it goes to the rightmost child first, instead of the leftmost first as above)
void dfs(int src) {
	s.push(v);
	while(!s.empty()) {
		v = s.top();
		s.pop();
		do(v);
		visited[v] = true;
		for(neigh : neighbors[v]) {
			if(!visited[neigh]) {
				s.push(neigh);
			}
		}
	}
}

// For BFS, we keep an "enqueued" boolean structure (instead of "visited" like in the DFS)
void bfs(int source) {
	q.push(source);
	enqueued.insert(source); // hash set
	while(!q.empty()) {
		v = q.front();
		q.pop();
		doSomething(v);
		for(int neigh : neighbors(v)) {
			if(enqueued.find(neigh) == enqueued.end()) {
				q.push(neigh);
				enqueued.insert(neigh);
			}
		}
	}
}

// BFS with depth is the same as above, we just keep a queue of pairs now! :D
void bfs_with_depth(int source) {
	q.push((source, 0));
	enqueued[source] = true;
	while(!q.empty()) {
		v, depth = q.front();
		q.pop();
		doSomething(v, depth);
		for(neigh : neighbors(v)) {
			if(!enqueued[neigh]) {
				q.push({neigh,  depth + 1});
				enqueued[neigh] = true;
			}
		}
	}
}

// BFS with levels - another way to also keep track of the depth, useful sometimes as in __rotting_oranges.cpp
void bfs_with_levels(int source) {
	queue<int> q;
    q.push(source);
    enqueued[source] = true;
    int curr_level = 0;
	
    while (!q.empty()) {
        int len = q.size();
        for (int i = 1; i <= len; ++i) {  // process the entire current level.
            int v = q.front();
            q.pop();
			doSomething(v);
            for(int neigh : neighbors(v)) {
				if(!enqueued[neigh]) {
					q.push(neigh);
					enqueued[neigh] = true;
				}
			}
        }
        ++curr_level;
    }
}

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

// Binary search
// See remember_sort_binary_search_and_lower_bound file too.
// It returns the location of x in given array arr[l..r] if present, otherwise -1
int binarySearch(const vector<int> &arr, int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2; // to avoid int overflow!
  
        // Check if x is present at mid 
        if (arr[m] == x) {
            return m; 
		}
   
        if (arr[m] < x) {
            l = m + 1; 
		} else {
            r = m - 1; 
		}
    }
  
    // if we reach here, then element was not present 
    return -1;
}

// Merge two sorted lists
// Sentinel idea very useful, like in the swap_nodes_in_pairs problem
// Can use "ans" as local stack variable here (no destructor defined to delete nexts and so on) 
// O(N+M) in time and O(1) in space (if used recursion calls there would be the recursion stack space N+M too).
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
  
// QuickSort below
// This function takes last element as pivot, places the pivot element at its correct position in sorted  
// array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot
int partition (vector<int> &arr, int low, int high) {  
    int pivot = arr[high]; // pivot, ideally a random in [low, high]
    int i = (low - 1); // index of smaller element  
  
    for(int j = low; j <= high - 1; ++j) {
        // If current element is smaller than the pivot  
        if (arr[j] < pivot) {
            swap(arr[++i], arr[j]); // increment index of smaller element  
        }  
    }

    swap(arr[++i], arr[high]); // put pivot in its right position

    return i; // final position of the pivot
}
  
// The main function that implements QuickSort  
// arr --> Array to be sorted in-place, not stable, O(n^2) in the worst case  
// low --> Starting index,  
// high --> Ending index
void quickSort(vector<int> &arr, int low, int high) {  
    if (low < high) {  
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);  
  
        // Separately sort elements before partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }
}

// Fast and Slow pointers (similar to Hare and Tortoise)
// Two halves: if we have an odd number of nodes the middle node will stay in the first half.
ListNode* endOfFirstHalf(ListNode* head) {
	if (!head) {
		return head;
	}

	ListNode* slow = head;
	ListNode* fast = head;
	while (fast->next && fast->next->next) { // useful like this to get the end of first half and not the start of 2nd half, handle if head is null at the beginning.
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
// Also useful to find if there is cycle in linked list.
bool hasCycle(ListNode* head) {
	if (!head) {
		return false;
	}

	ListNode* slow = head;
	ListNode* fast = head;
	while (fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			return true;
		}
	}

	return false;
}

// Revisit __course_schedule_dependecies.cpp for topo sort.
// Remember: topo sort is for *directed_ graphs*, for undirected ones think about simple DFS/BFS (maybe keeping 
// track of the "parent" to not "come back" if checking if it has no cycles) or even Union-Find - see __valid_tree.cpp
// To check the existence of cycles in a graph:
// 		For directed graphs see __course_schedule_dependecies.cpp (use topo ordering with indegrees and a queue similar to BFS - simpler to have only this by heart, remember topo ordering <=> no cycles, otherwise use DFS also backtracking current recursion_stack[v] bools)
// 		For undirected graphs see __valid_tree.cpp (use DFS from every unvisited node and keep track of parent to not "come back" skipping that already visited neighbor and not wrongly flagging a cycle there)
// 			Note: for normal DFS in undirected graphs there is no need to keep track of parent since not checking for cycles and the "parent" will already be marked as "visited" and then skipped - thus no infinite loop - see _count_connected_components_in_undirected_graph.cpp

// Revisit priority_queue syntax and syntax for str.substr(start, size).
	// std::size_t found = str.find(str2); 
		// size_t is an unsigned int
		// if str2 not found in str, returns std::string::npos (largest possible value for uint, equiv to -1 for uint)

// Revisit union-find:
	// Problem to find cycles in an undirected graph: https://www.geeksforgeeks.org/dsa/introduction-to-disjoint-set-data-structure-or-union-find-algorithm 
	// And also with path compression and union by rank (clearer path compression implementation here): https://www.geeksforgeeks.org/dsa/union-by-rank-and-path-compression-in-union-find-algorithm (also mentions the time and space complexities)
	// revisit problem __redundant_connection_union_find.cpp
	// 		one more example in _count_connected_components_in_undirected_graph.cpp

// Revisit problems with bitwise operation (find_the_single_solitary_number and find_single_number_thrice_context)
	// Also, remember that XOR is ^

// Revisit Counting Sort and Radix sort from My Notes.txt

// Hare and Tortoise to find entrance point of a cycle in Linked List: __find_the_duplicate_number.cpp (explanation link 
// of algorithm and my calculation proving that it works is also there). Additional fast and slow pointers above in "endOfFirstHalf" (use fast->next && fast->next->next) and also in _linked_list_cycle_detection.cpp

// Search "Sweep Line algorithm for Coding Interviews" on ChatGPT (transform input into events 
// like {time, +1} or {time, -1}) like in __meeting_rooms problem for min number of meeting rooms (same as "Max number of Overlapping Intervals"), and skyline problem too.

// upper_bound and lower_bound (remember_sort_binary_search_and_lower_bound.cpp)
// remember "int m = *std::max_element(v.begin(), v.end())" exists as well (O(N)), "min_element" too, "max({1, 3, 2})" (overloaded given vector initializer) works but max(v) does not! "max" is for only 2 elements "max(a, b)"
//     obs: if more than one element is largest, the iterator returned points to the first of such elements.
// can use "if(hash_map.count(el))" to check if we have a key "el" in the hash map (instead of .find != .end).

// Read over "My Notes.txt" briefly (trade-offs graph implementation, hash set for adjacency list good idea if you want to verify an edge in O(1))!

// Read Soldado's google doc with tips and my version of it with additional tips from other mocks as well (and more questions to ask the interviewer too).

// Review remember_trie.cpp briefly as well (remember to use pointers when managing tree-like structures and wanting
// to actually move through it and change it indeed and not a copy of it).

// Quickly see __lowest_common_ancestor.cpp (but in the case you have a "parent" pointer, can go up marking as visited from one and then go up from the other checking the first visited starting to check from the other itself)

int main(void) {
	cout << "QuickSort:" << endl;
    vector<int> arr = {10, 3, 40, 2, 4}; 
	printVector(arr);
	quickSort(arr, 0, arr.size()-1);
	printVector(arr);
	cout << endl;

	cout << "Binary search:" << endl;
	// arr from now on is {2, 3, 4, 10, 40}
    int x = 10; 
    int n = arr.size(); 
    int result = binarySearch(arr, 0, n - 1, x); 
    (result == -1) ? cout << "Element " << x << " is not present in array"
                   : cout << "Element " << x << " is present at index " << result; 

    return 0; 
}