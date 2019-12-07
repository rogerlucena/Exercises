#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/order-of-people-heights/
// Interesting problem
	// Approach using Segment Tree:
	// https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/

// You are given the following:

// A positive number N
// Heights : A list of heights of N persons standing in a queue
// Infronts : A list of numbers corresponding to each person (P) that gives the number of persons who are taller than P and standing in front of P
// You need to return list of actual order of persons’s height

// Consider that heights will be unique

// Example:

// Input: 
// Heights: 5 3 2 6 1 4
// InFronts: 0 1 2 0 3 2
// Output: 
// actual order is: 5 3 2 1 6 4 
// So, you can see that for the person with height 5, there is no one taller than him who is in front of him, and hence Infronts has 0 for him.

// For person with height 3, there is 1 person ( Height : 5 ) in front of him who is taller than him.

// You can do similar inference for other people in the list.

void insertInto(int number, int position, vector<int> &arr) {
    int tmpPointer = 0;
    int mainPtr = 0;
    while(tmpPointer < arr.size()) {
        if (mainPtr == position && arr[tmpPointer] == -1) {
            arr[tmpPointer] = number;
            return;
        }

        if (arr[tmpPointer] == -1) {
            mainPtr++;
            tmpPointer++;
        } else {
            tmpPointer++;
        }
    }
}

vector<int> order(vector<int> &A, vector<int> &B) {
	if(A.empty()) {
		return vector<int>();
	}

	vector<pair<int, int>> heightsAndInfronts;
	for(int i = 0; i < A.size(); ++i) {
		heightsAndInfronts.push_back({A[i], B[i]});
	}

	sort(heightsAndInfronts.begin(), heightsAndInfronts.end());

	vector<int> ans(A.size(), -1);
	for(int i = 0; i < heightsAndInfronts.size(); ++i) {
		int h = heightsAndInfronts[i].first;
		int infronts = heightsAndInfronts[i].second;
		
		insertInto(h, infronts, ans);
	}

	return ans;
}

int main() {
	vector<int> heights = {5, 3, 2, 6, 1, 4};
	vector<int> infronts = {0, 1, 2, 0, 3, 2}; // ans: {5, 3, 2, 1, 6, 4}

	printVector(order(heights, infronts));

	return 0;
}