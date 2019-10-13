#include <iostream>
#include <unordered_set>
#include <vector>
#include <math.h>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/find-duplicate-in-array/

// Given a read only array of n + 1 integers between 1 and n, find one number 
// that repeats in linear time using **less than O(n) space** and traversing the stream sequentially O(1) times.

// The solution below is O(sqrt(n)) in space
// Using sqrt for the size "l" of the intervals is a genius trick because it limitates 
// both the sizes of the vector "intervalsCount" (O(n/l)) and the set "s" later (O(l))
// ("l" and "n/l" will be both O(sqrt(n)) - final complexity in space :D )
// Ans: O(sqrt(n)) in memory and only 2 sequential passes through the stream.

int repeatedNumber(const vector<int> &A) {
	int n = A.size()-1;

	// Original way: using sqrt
	int l = ceil(sqrt((double) n)); //  interval size
	int nBuckets = ceil( ((double) n) / l );
	int m = n % l;

    // Trying to use log n in space (does not work - size of the set "s" below is not limited)
	// int nBuckets = floor(log((double) n));
	// nBuckets = nBuckets == 0 ? 1 : nBuckets;
	// int l = n / nBuckets; // interval size
	// int m = l;
	// if(n % nBuckets != 0) {
	// 	m = n % nBuckets;
	// 	nBuckets++;
	// }
	
	// cout << "l: " << l << endl;
	// cout << "nBuckets: " << nBuckets << endl;
	// cout << "m: " << m << endl;

	vector<int> intervalsCount (nBuckets, 0);

	for(int el : A) {
		++intervalsCount[(el-1)/l];
	} 

	int indexInterval = 0;
	for(; indexInterval < nBuckets; indexInterval++) {
		int count = intervalsCount[indexInterval];
		if(count > l || (indexInterval == nBuckets-1 && count > m)) {
			break;
		}
	}
	int intervalDown = indexInterval*l+1;
	int intervalUp = (indexInterval+1)*l;

	// cout << "intervalDown: " << intervalDown << endl;
	// cout << "intervalUp: " << intervalUp << endl;
	
	// cout << "vector intervalsCount: ";
	// printVector(intervalsCount);

	unordered_set<int> s = {};

	for(int el : A) {
		if(el < intervalDown || el > intervalUp) {
			continue;
		}
		if(s.find(el) != s.end()) {
			return el;
		}
		s.insert(el);
	}

	// cout << "s.size(): " << s.size() << endl;

	return -1;
}

int main() {
	vector<int> v = {3, 4, 1, 4, 1};
	// vector<int> v = {3, 2, 1, 4, 1};
	// vector<int> v = {3, 5, 1, 4, 2, 5};

	cout << repeatedNumber(v) << endl;

	return 0;
}