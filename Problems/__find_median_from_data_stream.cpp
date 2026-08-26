#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// https://leetcode.com/problems/find-median-from-data-stream
// Remember: nice solution is to use two heaps, a max-heap for the smallest nums and a min-heap for the largest ones,
// and keep the invariant that their sizes are equal or the `smallest` heap is 1 element larger than the other.
// Note: if asked to implement `.remove(val)`, remember to check the sizes of the heaps after each `remove` and rebalance if needed! (See Python solution below for that)

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


// Python solution:

/*
import heapq

class Container:
    """
    A container of integers that should support
    addition, removal, and search for the median integer.
    """
    
    def __init__(self):
        self.smallest = []  # Max heap.
        self.largest = []  # Min heap.

    def add(self, value: int) -> None:
        """
        Adds the specified value to the container

        :param value: int
        """
        # TODO: implement this method (done).
        heapq.heappush(self.smallest, -value)
        heapq.heappush(self.largest, -heapq.heappop(self.smallest))
        
        # Keep `self.smallest` with the extra element (if #elements is odd).
        self.rebalance_if_needed()

    def delete(self, value: int) -> bool:
        """
        Attempts to delete one item of the specified value from the container.

        :param value: int
        :return: True, if the value has been deleted, or
                 False, otherwise.
        """
        # TODO: implement this method (done).
        if self.is_empty():
            return False

        if value <= -self.smallest[0] and -value in self.smallest:
            self.smallest.remove(-value)
            self.rebalance_if_needed()
            return True

        if (
            self.largest  # A non-empty list in Python is truthy.
            and value >= self.largest[0]
            and value in self.largest
        ):
            self.largest.remove(value)
            self.rebalance_if_needed()
            return True

        return False

    def get_median(self) -> int:
        """
        Finds the container's median integer value, which is
        the middle integer when the all integers are sorted in order.
        If the sorted array has an even length,
        the leftmost integer between the two middle
        integers should be considered as the median.

        :return: The median if the array is not empty, or
        :raise:  a runtime exception, otherwise.
        """
        # TODO: implement this method (done).
        if self.is_empty():
            raise RuntimeError
        
        return -self.smallest[0]
    
    def is_empty(self) -> bool:
        """
        Check if the container has no data.
        
        :return: True if the container is empty, or
                 False otherwise.
        """
        return len(self.smallest) == 0
        
    def rebalance_if_needed(self) -> None:
        """
        If needed, rebalance the internal heaps to keep both with
        the same size or `self.smallest` with the extra element (invariant).
        """
        # Case: element deleted from `self.smallest`, or when adding.
        if len(self.smallest) < len(self.largest):
            heapq.heappush(self.smallest, -heapq.heappop(self.largest))
            
        # Case: element deleted from `self.largest`.
        if len(self.smallest) == len(self.largest) + 2:
            heapq.heappush(self.largest, -heapq.heappop(self.smallest))
*/