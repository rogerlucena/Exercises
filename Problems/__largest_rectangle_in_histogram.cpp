#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://www.interviewbit.com/problems/largest-rectangle-in-histogram/
// https://leetcode.com/problems/largest-rectangle-in-histogram/
// Note that the nature of this problem is different from container_most_water, cannot use two pointer here (the height of the rectangle is
// not defined by the columns on the border, but by the min heigh in range [left, right]).

// Given an array of integers A of size N. A represents a histogram i.e A[i] denotes height of
// the ith histogram’s bar. Width of each bar is 1. How big is the largest rectangle?

// Example:
// Input:
//     A = [2, 1, 5, 6, 2, 3]
// Output:
//     10
//     Explanation:
//     The largest rectangle is shown in the shaded area, which has area = 10 unit.

// Below you have solution with a stack - O(N) in time and space.
// There is a nice approach on leetcode with divide and conquer too: take the min heigh in total range [left, right], calculate the area of the
	// max rectangle including that min [it is min * (right-left+1)], recursion to the left side of min and right side, return the max area.
	// O(N log N) in time and O(log N) in space (recursion stack) in average, worst case (sorted input) is O(N^2) in time and O(N) in space.
int largestRectangleArea(vector<int> &A) {
	vector<int> a(A.begin(), A.end());
    a.push_back(0);
    int n = a.size();

    stack <int> s;
	int maxArea = 0;
    for(int i = 0; i < n;) {
		if(s.empty() || a[s.top()] <= a[i]) {
			s.push(i++);
		} else {
			int h = a[s.top()];
			s.pop();
			int l;
			
			if(!s.empty()) {
				l = s.top();
			} else {
				l = -1;
			}
			
			maxArea = max(maxArea, h * (i - (l + 1)));
		}
    }
    
    return maxArea;
}

int main() {
	vector<int> A = {2, 1, 5, 6, 2, 3};
	cout << "Answer: " << largestRectangleArea(A) << endl;

	return 0;
}