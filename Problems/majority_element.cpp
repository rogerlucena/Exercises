#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://www.interviewbit.com/problems/majority-element/

// Given an array of size n, find the majority element. The majority element is the element that appears more than floor(n/2) times.

// You may assume that the array is non-empty and the majority element always exist in the array.

// Example:
// Input: [2, 1, 2]
// Return: 2 which occurs 2 times which is greater than 3/2. 

// Website solution (more space efficient):
int majorityElement(vector<int> &A) {
	int majorityIndex = 0;
	for (int count = 1, i = 1; i < A.size(); ++i) {
		A[majorityIndex] == A[i] ? ++count : --count;
		if (count == 0) {
			majorityIndex = i;
			count = 1;
		}
	}

	return A[majorityIndex];
}

// Old solution below:
int oldMajorityElement(const vector<int> &A) {
	if(A.size() == 0) {
		throw "Empty array";
	}

	unordered_map<int, int> m;
	for(int i : A) {
		if(m.find(i) != m.end) {
			++m[i];
		} else {
			m[i] = 1;
		}
	}

	pair<int, int> maj = {INT_MIN, INT_MIN};
	for(pair<int, int> p : m) {
		if(p.second > maj.second) {
			maj = p;
		}
	}

	return maj.first;
}


int main() {
	cout << "Hello, World!";
	return 0;
}