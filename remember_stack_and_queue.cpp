// stack::push/pop
#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <queue>          // std::queue

// stack: push, top, pop
// queue: push, front, pop

// .empty() -> see if it is empty
// .size()

// Deque (in #include <queue>, erase invalidates the pointers to node, see lru_cache)
// front(), back(), at() (reference to the element there), push_back(), push_front(), void pop_back(), void pop_front()
// iterator insert (iterator position, const value_type& val);
// void insert     (iterator position, size_type n, const value_type& val) // n repetitions of val
// void insert     (iterator position, InputIterator first, InputIterator last)
// add just before "position" and return an "it" to the first of the newly added elements (first case)
// (same thing with std::list)


int main ()
{
    // Stack
    std::stack<int> mystack;

    for (int i=0; i<5; ++i) mystack.push(i);

    std::cout << "Popping out elements...";
    while (!mystack.empty())
    {
        std::cout << ' ' << mystack.top();
        mystack.pop();
    }
    std::cout << '\n';


    // Queue
    std::queue<int> myqueue;
    int myint;

    std::cout << "Please enter some integers (enter 0 to end):\n";

    do {
        std::cin >> myint;
        myqueue.push (myint);
    } while (myint);

    std::cout << "myqueue contains: ";
    while (!myqueue.empty())
    {
        std::cout << ' ' << myqueue.front();
        myqueue.pop();
    }
    std::cout << '\n';


    return 0;
}