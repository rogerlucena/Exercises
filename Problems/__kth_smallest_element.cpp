#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/kth-smallest-element-in-the-array/

// Find the kth smallest element in an unsorted array of non-negative integers.

// Inspiration: https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/

// Inspired in quick-sort (making changes in-place here)
// Worst case O(b^2), but normally O(n)
// (to improve the worst case use a median of medians to choose the pivot - divide it in ceil(n/5) gropus of five and sort each one to take the median)
void swapInts(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int partition(vector<int> &A, int l, int r) { // [l, r) -> "r" not inlcuded
	int i = l;
	int x = A[r-1];
	for(int j = l; j < r-1; ++j) {
		if(A[j] <= x) {
			swapInts(A[i++], A[j]);
		}
	}
	swapInts(A[i], A[r-1]);
	return i;
}

int kthsmallest(vector<int> &A, int B, int l, int r) {
	int pos = partition(A, l, r);
	if(pos-l == B-1) {
		return A[pos];
	} else if(pos-l > B-1) {
		return kthsmallest(A, B, l, pos);	
	} else {
		return kthsmallest(A, B-(pos-l+1), pos+1, r);
	}
}

int kthsmallest(vector<int> &A, int B) {
	return kthsmallest(A, B, 0, A.size());
}

// Solution with a max-heap, very elegant
// O(k + (n-k) log k) in time; B = k
// O(k) in space
int pqKthsmallest(const vector<int> &A, int B) {
	priority_queue<int> pq (A.begin(), A.begin() + B); // standard is the smaller cmp, so smaller = weak, greater = more priority

	for(int i = B; i < A.size(); ++i) {
		if(pq.top() > A[i]) {
			pq.pop();
			pq.push(A[i]);
		}
	}
	
	return pq.top();
}

// O(k n) in time
// O(1) in space
int oldKthsmallest(const vector<int> &A, int B) {
	if(A.size() == 0) {
		throw "Empty array \"A\"";
	}

	int kth = INT_MIN;
	for(int i = 0; i < B; ++i) {
		int rep = 0;
		int currSmaller = INT_MAX;
		for(int j = 0; j < A.size(); ++j) {
			if(A[j] < currSmaller && A[j] > kth) {
				currSmaller = A[j];
				rep = 0;
			} else if(A[j] == currSmaller) {
				++rep;
			} 
		}

		i += rep;
		kth = currSmaller;
	}

	return kth;
}

int main() {
	// vector<int> A = {2, 1, 4, 3, 2};
	// int k = 3; // ans expected: 2

	// vector<int> A = {8, 16, 80, 55, 32, 8, 38, 40, 65, 18, 15, 45, 50, 38, 
	// 				54, 52, 23, 74, 81, 42, 28, 16, 66, 35, 91, 36, 44, 9, 85, 
	// 				58, 59, 49, 75, 20, 87, 60, 17, 11, 39, 62, 20, 17, 46, 26, 81, 92};
	// int k = 9; // ans expected: 17

	vector<int> A = {94, 87, 100, 11, 23, 98, 17, 35, 43, 66, 34, 53, 72, 
					80, 5, 34, 64, 71, 9, 16, 41, 66, 96};
	int k = 19; // ans expected: 87

	cout << "Answer: " << kthsmallest(A, k) << endl;

	return 0;
}