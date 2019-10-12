#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://www.interviewbit.com/problems/wave-array/

// Given an array of integers, sort the array into a wave like array and return it,
// In other words, arrange the elements into a sequence such that a1 >= a2 <= a3 >= a4 <= a5.....
// (NOTE: If there are multiple answers possible, return the one thats lexicographically smallest)

vector<int> wave(vector<int> &A) {
   int size = A.size();
   if(size <= 1) {
	   return vector<int>(A);
   }

   vector<int> r = {};
   sort(A.begin(), A.end());
   
   for(int i = 0; i <= size-1; i+=2) {
	   if(i+1 < size) {
		   r.push_back(A[i+1]);
	   }
	   r.push_back(A[i]);
   }
   
   return r; 
}

void printVector(const vector<int> &arr) {
	for(int i = 0; i < arr.size(); i++) {
		cout << arr[i];
		if(i < arr.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

int main() {
	vector<int> v = {1, 2, 3, 4};
	
	cout << "input: ";
	printVector(v);

	cout << "output: ";
	printVector(wave(v));

	return 0;
}