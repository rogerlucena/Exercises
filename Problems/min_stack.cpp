#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

// https://leetcode.com/problems/min-stack/

// Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

// push(x) -- Push element x onto stack.
// pop() -- Removes the element on top of the stack.
// top() -- Get the top element.
// getMin() -- Retrieve the minimum element in the stack.

class MinStack {
	multiset<int> minHeap;
	stack<int> st;

public:
    /** initialize your data structure here. */
    MinStack() {

    }
    
    void push(int x) {
		st.push(x);
        minHeap.insert(x);
    }
    
    void pop() {
        int x = st.top();
		st.pop();
		minHeap.erase(minHeap.find(x));
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return *minHeap.begin();
    }
};

int main() {
	// Your MinStack object will be instantiated and called as such:
	MinStack* obj = new MinStack();
	int x = 4;
	int y = 3;
	obj->push(y);
	obj->push(x);
	int paramMin = obj->getMin();
	obj->pop();
	int paramTop = obj->top();

	cout << "paramMin: " << paramMin << ", paramTop: " << paramTop << endl; // ans: 3, 3

	return 0;
}