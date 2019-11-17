#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// Reverse in place a linked list
// merge two sorted linked lists
// sort a linked list? (merge sort)
// quick sort?

// For BFS, we keep an "enqueued" boolean structure (instead of "visited" like in the DFS)
void bfs(int source) {
	q.push(source);
	enqueued[source] = true;
	while(!q.empty()) {
		v = q.front();
		q.pop();
		doSomething(v);
		for(neigh : neighbors(v)) {
			if(!enqueued[neigh]) {
				q.push(neigh);
				enqueued[neigh] = true;
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
				q.push((neigh,  depth + 1));
				enqueued[neigh] = true;
			}
		}
	}
}

// DFS:
void dfs(v, visited) {
	visited[v] = true;
	for(neigh : neighbors(b)) {
		if(!visited(neigh)) {
			dfs(neigh);
		}
	}
}


// Binary search
// It returns the location of x in given array arr[l..r] if present, otherwise -1
int binarySearch(const vector<int> &arr, int l, int r, int x) { 
    while (l <= r) { 
        int m = l + (r - l) / 2; 
  
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
  
int main(void) { 
    vector<int> arr = { 2, 3, 4, 10, 40 }; 
    int x = 10; 
    int n = arr.size(); 
    int result = binarySearch(arr, 0, n - 1, x); 
    (result == -1) ? cout << "Element is not present in array"
                   : cout << "Element is present at index " << result; 

    return 0; 
}