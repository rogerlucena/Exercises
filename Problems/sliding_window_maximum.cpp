#include <iostream>
#include <vector>
#include <queue>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/sliding-window-maximum/

// Return an array with the max element of every sliding windown (in A) of size B

// Website solution
vector<int> slidingMaximum(const vector<int> &A, int B) {
    int w = B;
    int n = A.size();
    vector<int> C;
    if (n < w) {
        return C;
    }
    C.resize(n - w + 1);
    deque<int> Q;
    for (int i = 0; i < w; i++) {
        while (!Q.empty() && A[i] >= A[Q.back()])
            Q.pop_back();
        Q.push_back(i);
    }
    for (int i = w; i < n; i++) {
        C[i - w] = A[Q.front()];
        while (!Q.empty() && A[i] >= A[Q.back()])
            Q.pop_back();
        while (!Q.empty() && Q.front() <= i - w) // if index out of range, pop_front()
            Q.pop_front();
        Q.push_back(i);
    }
    C[n - w] = A[Q.front()];
    return C;
}

int getMax(const deque<int> &w) {
	int maxEl = INT_MIN;
	for(int el : w) {
		maxEl = max(maxEl, el);
	}
	return maxEl;
}

// One possible approach
vector<int> oldSlidingMaximum(const vector<int> &A, int B) {
	deque<int> w;
	int currMax = INT_MIN;
	for(int i = 0; i < B && i < A.size(); ++i) {
		w.push_back(A[i]);
		currMax = max(currMax, A[i]);
	}
	vector<int> C = {currMax};
	if(B >= A.size()) {
		return C;
	}

	for(int i = B; i < A.size(); ++i) {
		if(w.front() != currMax) {
			currMax = max(currMax, A[i]);
			w.pop_front();
			w.push_back(A[i]);
		} else {
			w.pop_front();
			w.push_back(A[i]);
			currMax = getMax(w);
		}
		C.push_back(currMax);
	}

	return C;
}



int main() {
	vector<int> A = {1, 3, -1, -3, 5, 3, 6, 7};
	int B = 3;
	cout << "Answer:" << endl;
	
	printVector(slidingMaximum(A, B));

	return 0;
}