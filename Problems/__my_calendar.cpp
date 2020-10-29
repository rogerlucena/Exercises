#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

// https://leetcode.com/problems/my-calendar-i/

// Implement a MyCalendar class to store your events. A new event can be added if adding the event will not cause a double booking.
// Your class will have the method, book(int start, int end). Formally, this represents a booking on the half open interval 
// [start, end), the range of real numbers x such that start <= x < end.

// A double booking happens when two events have some non-empty intersection (ie., there is some time that is common to both 
// events.)

// For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without 
// causing a double booking. Otherwise, return false and do not add the event to the calendar.

// Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)

// Example 1:
// MyCalendar();
// MyCalendar.book(10, 20); // returns true
// MyCalendar.book(15, 25); // returns false
// MyCalendar.book(20, 30); // returns true
// Explanation: 
// The first event can be booked.  The second can't because time 15 is already booked by another event.
// The third event can be booked, as the first event takes every time less than 20, but not including 20.
 
// Note:
// The number of calls to MyCalendar.book per test case will be at most 1000.
// In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].

// Nice idea below, when dealing with conflicting intervals think about binary trees -> average case is O(log n) to
// verify if interval conflicts (if random data - balanced tree), worst case it is still O(n).
// Practice with shared_ptr below. You can also use normal pointers but will have to define destructors and call delete.

// Time Complexity (Python): O(N^2) worst case, with O(N log N) on random data. For each new event, we insert 
// the event into our binary tree. As this tree may not be balanced, it may take a linear number of steps to add each event.
// Space Complexity: O(N), the size of the data structures used.
class Node {
	public:
	shared_ptr<Node> left;
	shared_ptr<Node> right;
	pair<int, int> interval;

	Node(int start, int end) {
		this->interval = {start, end};
		left = right = nullptr;
	}

	bool addNode(shared_ptr<Node> n) {
		if(!(n->interval.second <= this->interval.first || n->interval.first >= this->interval.second)) {
			return false;
		}

		if(n->interval.second <= this->interval.first) {
			if(this->left == nullptr) {
				this->left = n;
				return true;
			} else {
				return (*this->left).addNode(n);
			}
		} else {
			if(this->right == nullptr) {
				this->right = n;
				return true;
			} else {
				return (*this->right).addNode(n);
			}
		}
	}
};

class MyCalendar {
	shared_ptr<Node> calendar;
public:
    MyCalendar() {
		calendar = nullptr;
    }
    
    bool book(int start, int end) {
		if(calendar == nullptr) {
			calendar = shared_ptr<Node>(new Node(start, end));
			return true;
		} else {
			shared_ptr<Node> n = shared_ptr<Node>(new Node(start, end));
			return (*calendar).addNode(n);
		}
		
    }
};


int main() {
	MyCalendar c;
	cout << c.book(10, 20) << endl; // returns true
	cout << c.book(15, 25) << endl; // returns false
	cout << c.book(20, 30) << endl; // returns true
	return 0;
}