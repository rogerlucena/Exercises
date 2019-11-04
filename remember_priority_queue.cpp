#include <functional>
#include <queue>
#include <vector>
#include <iostream>

// top, push, pop
// Complexity of logn (worst case) to remove(fst) and to add (newElement)
// with Floyd's algorithm to construct a heap from another container: O(n) - very good; 
        // Floyd builds the tree from the bottom up (n/2 elements are leaves, n/4 have 
        // height 1 and so on, final complexity: n(1/2 + 1/4 + ...) = n) 
// (but to do the same, adding one element at a time -> O(n logn n))

// defaut comparator is smaller (as smaller -> as weak then, less priority), pop will give the greatest number

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

int main() {
    std::priority_queue<int> q;
    // priority_queue<int> pq (A.begin(), A.end()); // Initilize O(n) taking a container as input

    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q.push(n);

    print_queue(q); // defaut is "smaller" comparator, great numbers have better priority then

    std::priority_queue<int, std::vector<int>, std::greater<int> > q2;

    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q2.push(n);

    print_queue(q2);

    // Using lambda to compare elements.
    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1);}; // XOR (exclusive or)
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);

    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q3.push(n);

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