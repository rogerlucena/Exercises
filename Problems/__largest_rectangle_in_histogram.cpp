#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://www.interviewbit.com/problems/largest-rectangle-in-histogram/

// Given an array of integers A of size N. A represents a histogram i.e A[i] denotes height of
// the ith histogram’s bar. Width of each bar is 1. Hiw big is the largest rectangle?

// Example:
// Input:
//     A = [2, 1, 5, 6, 2, 3]
// Output:
//     10
//     Explanation:
//     The largest rectangle is shown in the shaded area, which has area = 10 unit.

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