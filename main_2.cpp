#include <iostream>
#include <vector>

using namespace std;

int main() {
	cout << "Hello, World!";
	return 0;
}


/*

#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>

using namespace std;

// https://leetcode.com/problems/lru-cache/
// Take the best of both worlds: O(1) access time with a hash map and use a deque to control the timestamps 

class LRUCache {
private:
	int capacity;
	deque<pair<int, int>> dq;
	unordered_map<int, deque<pair<int, int>>::iterator> m;

	void moveFront(deque<pair<int, int>>::iterator it) {
		pair<int, int> p = *it;
		dq.erase(it);
		dq.push_front({p.first, p.second});
		m[p.first] = dq.begin();
	}

public:
    LRUCache(int capacity) {	
		this->capacity = capacity;
		dq.clear();
		m.clear();
    }
    
    int get(int key) {
        if(m.find(key) != m.end()) {
			moveFront(m[key]);
			return (*m[key]).second;
		}	

		return -1;
    }
    
    void put(int key, int value) {
		if(m.find(key) != m.end()) {
			(*m[key]).second = value;
			moveFront(m[key]);
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
	unordered_map<int,int> m;
	m[2]++; // default value seems to be 0
	cout << "v: " << m[2] << endl; // 1

	deque<int> dq = {1, 2};
	deque<int>::iterator it = dq.begin();
	deque<int>::iterator it2 = dq.begin()+1;
	cout << "it: " << (*it) << endl;

	dq.erase(it2);
	dq.push_front(2);
	cout << "it: " << (*it) << endl;

	return 0;
}

*/