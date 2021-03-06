#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// https://www.pramp.com/challenge/aK6V5GVZ9MSPqvG1vwQp

// Given an array arr of unique nonnegative integers, implement a function getDifferentNumber 
// that finds the smallest nonnegative integer that is NOT in the array.

// Example in main()

// in-place solution, O(N) in time and constant space!
int getDifferentNumber(vector<int> &arr) {
	for(int i = 0; i < arr.size(); ++i) {
		int tmp = arr[i];
		while(tmp < arr.size() && arr[tmp] != tmp) {
			swap(tmp, arr[tmp]);
		}
	}

	for(int i = 0; i < arr.size(); ++i) {
		if(i != arr[i]) {
			return i;
		}
	}

	return arr.size();
}

// O(N) in time and space below, we can still improve space!
int oldGetDifferentNumber(const vector<int> &arr) {
	unordered_set<int> s;
	for(int el : arr) {
		s.insert(el);
	}

	for(int i = 0; i < INT_MAX; ++i) {
		if(s.find(i) == s.end()) {
			return i;
		}
	}

	return -1;
}

int main() {
	vector<int> v ={0, 1, 2, 4}; // ans: 3
	cout << "Answer: " << getDifferentNumber(v) << endl;

	return 0;
}