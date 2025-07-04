#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://neetcode.io/problems/largest-rectangle-in-histogram - less immediate solution with only one pass here (https://youtu.be/zx5Sw9130L0?si=1yc47uwo87UDYkmk)
// https://leetcode.com/problems/largest-rectangle-in-histogram
// https://www.interviewbit.com/problems/largest-rectangle-in-histogram/
// Hard, use stack to create leftmost and rightmost auxiliar arrays - stack useful when wanting the most recent to operate with.
// Note that the nature of this problem is different from container_most_water, cannot use two pointer here (the height of the rectangle is
// not defined by the columns on the border, but by the min heigh in range [left, right]).

// You are given an array of integers heights where heights[i] represents the height of a bar. The width of each bar is 1.
// Return the area of the largest rectangle that can be formed among the bars.
// Note: This chart is known as a histogram.

// Example 1:
// Input: heights = [7,1,7,2,2,4]
// Output: 8

// Example 2:
// Input: heights = [1,3,7]
// Output: 7

// Constraints:
// 1 <= heights.length <= 1000.
// 0 <= heights[i] <= 1000

// More intuitive solution, O(N) for time and space.
// For each "i" use that "heigh[i]"" and tries to expand to left and right until finding a smaller height - use stack 
// to build "leftmost" and "rightmost" in O(N).
int largestRectangleArea(vector<int>& heights) {
	int n = heights.size();
    vector<int> leftmost(n, -1); // index of the first smaller height to the left.
	vector<int> rightmost(n, n); // index of the first smaller height to the right.
	stack<int> st;
	
	for (int i = 0; i < n; ++i) {
		while (!st.empty() && heights[st.top()] >= heights[i]) {
			st.pop();
		}
		if (!st.empty()) {
			leftmost[i] = st.top();
		}
		st.push(i);
	}

    while (!st.empty()) st.pop();

    for (int i = n - 1; i >= 0; --i) {
		while (!st.empty() && heights[st.top()] >= heights[i]) {
			st.pop();
		}
		if (!st.empty()) {
			rightmost[i] = st.top();
		}
		st.push(i);
    }

	int max_area = 0;
	for (int i = 0; i < n; ++i) {
		int curr_area = heights[i] * (rightmost[i] - leftmost[i] - 1);	
		max_area = max(max_area, curr_area);
	}

	return max_area;
}

// Below you have solution with a stack - O(N) in time and space, but only 1 pass.
// There is a nice approach on leetcode with divide and conquer too: take the min heigh in total range [left, right], calculate the area of the
	// max rectangle including that min [it is min * (right-left+1)], recursion to the left side of min and right side, return the max area.
	// O(N log N) in time (because N for min inicial + 2*N/2 + 4*N/4 + ... log N times) and O(log N) in space (recursion stack) in average, 
	// worst case (sorted input) is O(N^2) in time and O(N) in space.
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
    } // if we have equal bars in the stack, the first one added will give the complete area of that rectangle and the others will be smaller.
    
    return maxArea;
}

int main() {
	vector<int> A = {2, 1, 5, 6, 2, 3};
	cout << "Answer: " << largestRectangleArea(A) << endl;

	return 0;
}