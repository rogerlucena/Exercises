#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://www.interviewbit.com/problems/assign-mice-to-holes/
// Greedy algorithms

// There are N Mice and N holes are placed in a straight line.
// Each hole can accomodate only 1 mouse.
// A mouse can stay at his position, move one step right from x to x + 1, or move one step left from x to x − 1. Any of these moves consumes 1 minute.
// Assign mice to holes so that the time when the last mouse gets inside a hole is minimized.

// Example:
// positions of mice are:
// 4 -4 2
// positions of holes are:
// 4 0 5

// Assign mouse at position x=4 to hole at position x=4: Time taken is 0 minutes 
// Assign mouse at position x=-4 to hole at position x=0: Time taken is 4 minutes 
// Assign mouse at position x=2 to hole at position x=5: Time taken is 3 minutes 
// After 4 minutes all of the mice are in the holes.

// Since, there is no combination possible where the last mouse's time is less than 4, 
// answer = 4.

// Greedy Idea: sort both and remember: max(|i1 - j1|, |i2 - j2|) <= max(|i1 - j2|, |i2 - j1|)
// Since it follows by induction that every assignment can be transformed by a series of swaps 
// into the sorted assignment, where none of these swaps increases the makespan, we are done
int mice(vector<int> &A, vector<int> &B) {
	assert(A.size() == B.size());
	if(A.size() == 0) {
		return 0;
	}

	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	int ans = INT_MIN;
	for(int i = 0; i < A.size(); ++i) {
		ans = max(ans, abs(A[i] - B[i]));
	}

	return ans;
}


int main() {
	cout << "Hello, World!";
	return 0;
}