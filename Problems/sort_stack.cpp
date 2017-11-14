#include <iostream>
#include<stack>

using namespace std;

/*

-- Problem statement:

Implement a way to sort a stack of int numbers, using at most the space of another stack


*/

// My solution> O(n) in space and O(n^2) in time

inline void iterativeStep(stack<int> &s1, stack<int> &s2){
    int top1 = s1.top();
    s1.pop();

    int count = 0;

    while(!s2.empty() && top1 > s2.top()) {
        s1.push((int) s2.top());
        s2.pop();
        ++count;
    }

    s2.push(top1);

    while(count > 0) {
        s2.push((int) s1.top());
        s1.pop();
        --count;
    }
}

int main() {
    stack<int> s1; // original stack, filled below
    s1.push(7);
    s1.push(4);
    s1.push(6);
    s1.push(5);

    stack<int> s2; // auxiliar one

    while (!s1.empty()) {
        iterativeStep(s1, s2); // keeping s2 sorted
    }

    // Printing the solution
    // Has to be 4, 5, 6, 7 -> ascending order
    while(!s2.empty()) {
        cout << s2.top() << endl;
        s2.pop();
    }

    return 0;
}
