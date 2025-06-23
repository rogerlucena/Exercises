#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

// top, push, pop
// Complexity of logn (worst case) to remove(fst) and to add (newElement)
// with Floyd's algorithm to construct a heap from another container: O(n) - very good; 
        // Floyd builds the tree from the bottom up (n/2 elements are leaves, n/4 have 
        // height 1 and so on, final complexity: n(1/2 + 1/4 + ...) = n) 
// // priority_queue<int> pq (A.begin(), A.end()); // Initilize O(n) taking a container as input
// (but to do the same, adding one element at a time -> O(n log n))

// Note: you can also implement a pq using a set, but seems to be slower (since you can also iterate it all in sorted manner).
// do this only when you want to have id_to_val hash map and update val for given id, see My Notes.

// defaut comparator is smaller (as smaller -> as weak then, less priority), pop will give the greatest number

// General syntax:
// auto cmp = [](int left, int right) {return left > right;};
// priority_queue<int, vector<int>, decltype(cmp)> q3(container.begin(), container.end(), cmp);
// priority_queue<int, vector<int>, decltype(cmp)> q3(cmp, container);
// or:
// priority_queue<int, vector<int>, greater<int>> q2;

// eg of cmp for pq with hash map:
// auto cmp = [](const pair<char, int> &p1, const pair<char, int> &p2) {return p1.second < p2.second;};
// priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> mostCommon(count.begin(), count.end(), cmp);

// Also works using a class:
// class Compare {
// public:
//     bool operator() (Foo, Foo) {
//         return true;
//     }
// };
// int main() {
//     std::priority_queue<Foo, std::vector<Foo>, Compare> pq;
//     return 0;
// }

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

int main() {
    std::priority_queue<int> q1;
    // priority_queue<int> pq(A.begin(), A.end()); // Initilize O(n) taking a container as input

    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q1.push(n);

    std::cout << "q1: ";
    print_queue(q1); // defaut is "smaller" comparator, great numbers have better priority then

    std::priority_queue<int, std::vector<int>, std::greater<int>> q2;

    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q2.push(n);

    std::cout << "q2: ";
    print_queue(q2);

    // Good way of initializing, using lambda and vector as arguments
    // Using lambda to compare elements.
    // auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1);}; // XOR (exclusive or)
    auto cmp = [](int left, int right) {return left > right;};
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp, {1,8,5,6,3,4,0,9,7,2});

    std::cout << "q3: ";
    print_queue(q3);

    int arr[] = {1, 3, 2, 6, 6, 5};
    std::priority_queue<int> mypq(arr, arr+6); // only int, default underlying container is vector<int>, created from int array pointers, defaut comparator is smaller (as smaller, as weak then)
    print_queue(mypq);

}

/*
-- Output:
9 8 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 8 9
8 9 6 7 4 5 2 3 0 1

http://en.cppreference.com/w/cpp/container/priority_queue
*/

/*
    // Priority queue - syntax:
    priority_queue<int, vector<int>, greater<int>> pq(numbers, numbers+nNumbers);
    // Testing the priority_queue - iteration
    while(!pq.empty()){
        cout << pq.top() << " ";
        pq.pop();
    }
*/

// Code testing syntax:
// Set and Priority Queue
int main2() {
	auto cmp = [](const string &a, const string &b) { return a.size() < b.size(); };
    set<string, decltype(cmp)> s(cmp);

	s.insert("a");
	s.insert("abc");
	s.insert("ab");

	cout << "C++ set:" << endl;
	for(string st : s) {
		cout << st << endl;
	}
	// a
	// ab
	// abc
	cout << endl;

	cout << "Priority queue:" << endl;
	priority_queue<string, vector<string>, decltype(cmp)> pq(cmp, {"a", "abc", "ab"});
	for(; !pq.empty(); pq.pop()) {
		cout << pq.top() <<  endl;
	}
	// abc
	// ab
	// a

	return 0;
}