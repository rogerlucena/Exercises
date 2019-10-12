#include <iostream>
#include <vector>

using namespace std;

void printVector(const vector<int> &arr) {
	for(int i = 0; i < arr.size(); i++) {
		cout << arr[i];
		if(i < arr.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

void printMatrix(const vector<vector<int>> &m) {
	for(int i = 0; i < m.size(); i++) {
		printVector(m[i]);
	}
}