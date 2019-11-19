#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// https://leetcode.com/problems/find-median-from-data-stream/submissions/

// Median is the middle value in an ordered integer list. If the size of the list is even, there is 
// no middle value. So the median is the mean of the two middle value.

// For example,
// [2,3,4], the median is 3
// [2,3], the median is (2 + 3) / 2 = 2.5

// Design a data structure that supports the following two operations:
// void addNum(int num) - Add a integer number from the data stream to the data structure.
// double findMedian() - Return the median of all elements so far.
 
// Example:

// addNum(1)
// addNum(2)
// findMedian() -> 1.5
// addNum(3) 
// findMedian() -> 2

class MedianFinder {
	priority_queue<int> smaller;
	priority_queue<int, vector<int>, std::greater<int>> greater;

	public:
    // Initialize your data structure here
    MedianFinder() {}
    
    void addNum(int num) {
        smaller.push(num);

		greater.push(smaller.top()); // balancing
		smaller.pop();

		if(greater.size() > smaller.size()) {
			smaller.push(greater.top()); // keep always the smaller as the bigger (or same size) one
			greater.pop();
		}
		
    }
    
    double findMedian() {
		return smaller.size() != greater.size() ? smaller.top() : (smaller.top() + greater.top()) / 2.0;
    }
};

int main() {
	cout << "Hello, World!";
	return 0;
}