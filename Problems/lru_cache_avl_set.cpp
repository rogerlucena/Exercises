#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

// https://www.interviewbit.com/problems/lru-cache/
// old LRU with heap

// Design and implement a data structure for LRU (Least Recently Used) cache. It should support the following operations: get and set.

// get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
// set(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should 
// invalidate the least recently used item before inserting the new item.
// The LRU Cache will be initialized with an integer corresponding to its capacity. Capacity indicates the maximum number of 
// unique keys it can hold at a time.

// Definition of “least recently used” : An access to an item is defined as a get or a set operation of the item. “Least 
// recently used” item is the one with the oldest access time.

// Example:
// Input: 
//          capacity = 2
//          set(1, 10)
//          set(5, 12)
//          get(5)        returns 12
//          get(1)        returns 10
//          get(10)       returns -1
//          set(6, 14)    this pushes out key = 5 as LRU is full. 
//          get(5)        returns -1 


// auto cmp = [](const pair<int, int> &p, const pair<int, int> &q) -> bool {return p.first < q.first;};

// class cmp {
// public:
// 	bool operator() (const pair<int, int> &p, const pair<int, int> &q) const {
// 		return p.first < q.first;
// 	}
// };

class LRUCache {
	int capacity;
	int t;
	unordered_map<int, pair<int, int>> data; // key, pair (value, lastAccessTime)
	set<pair<int, int>> minHeap; // pair (lastAccessTime, key)
	void updateTime(int key); 

public:
	LRUCache(int capacity);
	int get(int key);
	void set(int key, int value);
	void printHeap();
};

LRUCache::LRUCache(int capacity) {
	this->capacity = capacity;
	this->t = 0;
	data.clear();
	minHeap.clear();
}

void LRUCache::updateTime(int key) {
	int value = data[key].first;
	int lastAccess = data[key].second;

	minHeap.erase({lastAccess, key});
	minHeap.insert({t, key});
	data[key] = {value, t};
}

void LRUCache::printHeap() {
	cout << "minHeap:" << endl;
	for(auto p : minHeap) {
		cout << "p: " << p.first << ", " << p.second << endl;
	}
}

int LRUCache::get(int key) {
	++t;
	if(data.find(key) == data.end()) {
		return -1;
	}
	
	updateTime(key);
	return data[key].first;
}

void LRUCache::set(int key, int value) {
	++t;
	
	if(data.find(key) != data.end()) {
		updateTime(key);
		data[key] = {value, t};
		return;
	}

	if(capacity == 0) {
		pair<int, int> lru = *minHeap.begin();
		// cout << "Erasing: " << lru.second << ", time: " << lru.first << endl;
		// cout << "Inserting: " << key << ", val: " << value << endl;
		data.erase(lru.second);
		minHeap.erase(lru);
		++capacity;
	}

	data[key] = {value, t};
	minHeap.insert({t, key});
	--capacity;
}

int main() {
	LRUCache cache(2);

	// cout << cache.get(2) << endl;
	// cache.set(2, 6);
	// cout << cache.get(1) << endl;
	// cache.set(1, 5);
	// cache.set(1, 2);
	// cout << cache.get(1) << endl;
	// cout << cache.get(2) << endl; // ans: -1 -1 2 6 

	cache.set(2, 1);
	cache.set(1, 1);
	cache.set(2, 3);
	cache.set(4, 1);
	// cache.printHeap();
	cout << cache.get(1) << endl;
	cout << cache.get(2) << endl; // ans: -1 3

	return 0;
}


// Ex:
// 6 2 
// S 2 1 
// S 1 1 
// S 2 3 
// S 4 1 
// G 1 
// G 2

// my ans: 1 -1 
// expected: -1 3



// capacity: 0
// time: 5
// data: {2: 6, 2}, {1: 2, 5}
// minHeap: {2, 2}, {5, 1}

// Ex:
// 7 2 
// G 2 -> -1
// S 2 6 
// G 1  -> -1
// S 1 5 
// S 1 2 
// G 1 -> 2
// G 2 -> should be 6

// my ans: -1 -1 2 -1 
// expected: -1 -1 2 6 
