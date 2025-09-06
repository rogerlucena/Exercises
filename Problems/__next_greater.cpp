#include <iostream>
#include <vector>
#include <stack>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/nextgreater 
// https://leetcode.com/problems/next-greater-element-ii (version with circular array below)
// Remember: use stack to do it in-place, good exemple of exercise using stack. Case with circular array is below.

// Given an array, find the next greater element G[i] for every element A[i] in the array. The Next greater 
// Element for an element A[i] is the first greater element on the right side of A[i] in array.
// More formally,

// G[i] for an element A[i] = an element A[j] such that 
//     j is minimum possible AND 
//     j > i AND
//     A[j] > A[i]
// Elements for which no greater element exist, consider next greater element as -1.

// Example:
// Input : A : [4, 5, 2, 10]
// Output : [5, 10, 10, -1]

// Example 2)
// Input : A : [3, 2, 1]
// Output : [-1, -1, -1]

vector<int> nextGreater(vector<int> &A) {
	int size = A.size();
	if(size == 0) {
		return A;
	}

	stack<int> s;
	s.push(0);

	for(int i = 1; i < size; ++i) {
		int next = A[i];
		while(!s.empty() && next > A[s.top()]) {
			A[s.top()] = next;
			s.pop();
		}
		s.push(i);
	}

	while(!s.empty()) {
		A[s.top()] = -1;
		s.pop();
	}

	return A;
}

// https://leetcode.com/problems/next-greater-element-ii (version with circular array)
// Remember: iterate twice over the array to simulate circularity, in the final pass it will let all "next_greater"
// values updated considering all the elements to the right (all the elements of "nums", as it should be for a circular array).

// Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), return the next greater 
// number for every element in nums.

// The next greater number of a number x is the first greater number to its traversing-order next in the array, which 
// means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.

// Example:
// Input: nums = [1,2,1]
// Output: [2,-1,2]

vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> next_greater(n);
    stack<int> st;
    for (int i = 2 * n - 1; i >= 0; --i) {  // iterate twice over the array to simulate circularity.
        int pos = i % n;
        while (!st.empty() && nums[pos] >= st.top()) {
            st.pop();
        }
        next_greater[pos] = st.empty() ? -1 : st.top();
        st.push(nums[pos]);
    }

    return next_greater;
}

int main() {
	vector<int> A = {4, 5, 2, 10};
	// vector<int> A = {3, 2, 1};

	cout << "Answer:" << endl;
	printVector(nextGreater(A));

	return 0;
}