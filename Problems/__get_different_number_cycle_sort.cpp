#include <iostream>
#include <vector>
#include <unordered_set>

#include "tools.cpp"

using namespace std;

// https://www.pramp.com/challenge/aK6V5GVZ9MSPqvG1vwQp
// Idea: remember cycle-sort for the inplace solution

// Given an array arr of unique nonnegative integers, implement a function 
// getDifferentNumber that finds the smallest nonnegative integer that is NOT in the array.

// in-place solution, cycle-sort
int getDifferentNumber(vector<int> &arr) {
	for(int i = 0; i < arr.size(); ++i) {
		// int tmp = arr[i];
		while(arr[i] < arr.size() && arr[i] != i) {
			swap(arr[i], arr[arr[i]]);
		}
	}

	for(int i = 0; i < arr.size(); ++i) {
		if(i != arr[i]) {
			return i;
		}
	}

	return arr.size();
}

int getDifferentNumberNotInplace(const vector<int> &arr) {
  // your code goes here
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
  vector<int> v ={0, 2, 3, 4, 1}; // ans: 5
  cout << "Answer: " << getDifferentNumber(v) << endl;
  printVector(v);
  
  return 0;
}