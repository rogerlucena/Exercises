#include <iostream>
#include <vector>
#include <map>

using namespace std;

// "<set>" is a heap based set,  "<map>" is a heap map

// remember: the default cmp here is smaller too, .begin() -> .end() will be sorted then (the "priority" idea is only for pq! not here)
// remember: we have std::lower_bound() and upper_bound() in <algorithms> too, like here

// The advantage here, compared to priority_queue for example,
// is that you can go through the sorted list in linear time,
// also, you can use "upper_bound" and "lower_bound" functions in logarithmic time (useful in some cases)

// Other differences: "set" does not allow duplicates, "priority_queue" allows ("multiset" allows too)
// building a heap "priority_queue" is also linear on the number of items (Floyd's algorithm), whereas building a set/map 
// is O(N log N) (otherwise we would have found a faster way of sorting!)
// (unless it's being built from a sequence that's already ordered - in which case it is also linear).

// remember, for maps and sets we cannot do operations with the iterators such 
// as "m.upper_bound(n) - m.begin()", or "m.begin()+1" (bidirectional iterators do not allow it), only ++ or -- 

// "set/map/multiset" are normally implemented over binary search trees (AVL or RB trees)
// "priority_queues" are implemented over balanced heaps (!= than BSTs)

// In C++ STL - implemented internally using balanced red black trees.
// "map" below, "set" is similar: 

int main() {
    // With a personalized comparator:
    auto cmp = [](const string &a, const string &b) { return a.size() < b.size(); };
    map<string, string, decltype(cmp)> m(cmp); // similar and set (without de 2nd parameter <>) 
                                                      // and priority_queue (with a parameter for the underlying container I believe)

    map<int, int> A; // O(1) declaration which declares an empty tree map.
    int K = 3;
    int V = 7;
    int x = 37;

    // Insert a new key, value pair K, V:
    A[K] = V; // O(log n). Note that we expect key K to be unique here. If you have keys that will repeat, take a look at multimaps. 

    // Delete a key K:
    A.erase(K); // O(log n)
    
    // Search if a key K exists in map:
    A.find(K) != A.end();  // O(log n)
    
    // Search for the value with key K:
    A[K];     // O(log n)

    // Find minimum key K in the map ( if the map is not empty ) :
    (A.begin())->first;     // O(1)

    // Find maximum key K in the map ( if map is not empty ) :
    (A.rbegin())->first;     // O(1)

    // Iterate over keys in sorted order :
    for (map<int,int>::iterator it = A.begin(); it != A.end(); ++it) {
        // it->first has the key, it->second has the value. 
    }

    // Iterators returned below:
    // Find closest key K > x :
    (A.upper_bound(x))->first;     // O(log n). Returns A.end() in the case when x is more than or equal to the max key in the map. 

    // Find closest key K >= x :
    (A.lower_bound(x))->first;     // O(log n). Returns A.end() in the case when x is more than the max key in the map.

    // Size ( number of entries in the map ) :
    A.size();

    // Same for "set"

	return 0;
}