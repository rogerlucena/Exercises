#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://www.interviewbit.com/problems/longest-consecutive-sequence/

// Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

// Example:
// Given [100, 4, 200, 1, 3, 2],
// The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

// Your algorithm should run in O(n) complexity.

int longestConsecutive(const vector<int> &A) {
	int longestSize = 0;
	unordered_map<int, int> m;
	for(int el : A) {
		m[el] = 1;
	}

	for(int el : A) {	
		if(m[el] == 0) {
			continue;
		}

		int currSize = 1;
		++el;
		while(m.find(el) != m.end()) {
			m[el] = 0; // key element to make it O(n) in time
			++el;
			++currSize;
		}

		longestSize = max(longestSize, currSize);
	}

	return longestSize;
}


int main() {
	vector<int> A = {100, 4, 200, 1, 3, 2};
	cout << "Answer: " << longestConsecutive(A) << endl;

	return 0;
}