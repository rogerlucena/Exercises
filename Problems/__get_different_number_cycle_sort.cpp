#include <iostream>
#include <vector>
#include <unordered_set>

#include "tools.cpp"

using namespace std;

// https://www.pramp.com/challenge/aK6V5GVZ9MSPqvG1vwQp
// Idea: remember cycle-sort for the inplace solution
// Note: original cycle-sort is O(N^2) - for each number puts it in the right position by counting the number of items smaller than it (https://www.geeksforgeeks.org/cycle-sort/).
// Plus: link with hare and tortoise algorithm better explained: https://leetcode.com/problems/find-the-duplicate-number/solution/
// (detection of the only repeated number in O(N), detects the entrance point of a cycle in a linked list, hare twice as fast
// as the tortoise - see final code, or the second to last idea using bits) - problem also in __find_the_duplicate_number.cc

// Given an array arr of unique nonnegative integers, implement a function 
// getDifferentNumber that finds the smallest nonnegative integer that is NOT in the array.

// in-place solution, cycle-sort
// O(N) in time and O(1) in space (every number is swaped only once here, do not let the 2 loops fool you). 
// Another solution is to use an auxiliar hash set, but then you get O(N) in space.
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