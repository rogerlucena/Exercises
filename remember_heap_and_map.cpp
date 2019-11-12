#include <iostream>
#include <vector>
#include <map>

using namespace std;

// heap is "set", map is "map"

// The advantage here, compared to priority_queue for example,
// is that you can go through the sorted list in linear time,
// also, you can use "upper_bound" and "lower_bound" functions in logarithmic time (useful in some cases)
// remember, here we cannot do operations with the iterators such 
// as "m.upper_bound(n) - m.begin()", or "m.begin()+1" (bidirectional iterators do not allow it), only ++ or -- 

// C++ Standard Template Library provides maps and sets which are implemented > internally 
// using balanced red black trees. We explore maps here for now, although set is very much similar. Map declaration :

int main() {
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

    // Find closest key K > x :
    (A.upper_bound(x))->first;     // O(log n). Do need to handle the case when x is more than or equal to the max key in the map. 

    // Find closest key K >= x :
    (A.lower_bound(x))->first;     // O(log n). Do need to handle the case when x is more than the max key in the map.

    // Size ( number of entries in the map ) :
    A.size();

    // Same for "set"

	return 0;
}