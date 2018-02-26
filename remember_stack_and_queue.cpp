// stack::push/pop
#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <queue>          // std::queue

// stack: push, top, pop
// queue: push, front, pop

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