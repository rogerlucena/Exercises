#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

// https://leetcode.com/problems/lru-cache/
// Take the best of both worlds: O(1) access time with a hash map and use a doubly linked list to control the timestamps 

// Design and implement a data structure for Least Recently Used (LRU) cache. It should support the 
// following operations: get and put.

// get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
// put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, 
// it should invalidate the least recently used item before inserting a new item.

// The cache is initialized with a positive capacity.

// Follow up:
// Could you do both operations in O(1) time complexity?

// Example:

// LRUCache cache = new LRUCache( 2 /* capacity */ );

// cache.put(1, 1);
// cache.put(2, 2);
// cache.get(1);       // returns 1
// cache.put(3, 3);    // evicts key 2
// cache.get(2);       // returns -1 (not found)
// cache.put(4, 4);    // evicts key 1
// cache.get(1);       // returns -1 (not found)
// cache.get(3);       // returns 3
// cache.get(4);       // returns 4

class LRUCache {
private:
	int capacity;
	list<pair<int, int>> dq;
	unordered_map<int, list<pair<int, int>>::iterator> m;

	void moveFront(int key, int val) {
		dq.erase(m[key]);
		dq.push_front({key, val});
		m[key] = dq.begin();
	}

public:
    LRUCache(int capacity) {	
		this->capacity = capacity;
		dq.clear();
		m.clear();
    }
    
    int get(int key) {
        if(m.find(key) != m.end()) {
			int val = (*m[key]).second;
			moveFront(key, val);
			return val;
		}	

		return -1;
    }
    
    void put(int key, int value) {
		if(m.find(key) != m.end()) {
			moveFront(key, value);
			return;
		} 

		if(capacity == 0) {
			pair<int, int> p = dq.back();
			m.erase(p.first);
			dq.pop_back();
			++capacity;
		}
        
		dq.push_front({key, value});
		m[key] = dq.begin();
		--capacity;
    }
};

int main() {
	LRUCache cache(10);
	cache.put(7, 28);
	cache.put(7, 1);
	cache.put(8, 15);
	cout << cache.get(6) << endl; // -1
	cache.put(10, 27);
	cache.put(8, 10);
	cout << cache.get(8) << endl; // 10
	cache.put(6, 29);
	cache.put(1, 9);
	cout << cache.get(6) << endl; // 29
	cache.put(10, 7);
	cout << cache.get(1) << endl; // 9

	return 0;
}

// ["LRUCache","put","put","put","get","put","put",  "get","put","put","get","put","get","get","get","put","put","get","put","get"]
// [[10],     [7,28],[7,1],[8,15],[6], [10,27],[8,10],[8],[6,29],[1,9],[6],  [10,7],*[1],  [2], [13], [8,30],[1,5],[1],[13,2],[12]]

// Expected
// [null,null,null,null,-1,null,null,10,null,null,29,null,*9, -1,-1,null,null,5,null,-1]

// cap: 5
// m: [7, &1], [8, &2], [10, &3], [6, &4], [1, &5]
// dq: &3[10, 7], &4[6, 29], &5[1, 9], &2[8, 10], &1[7, 1],