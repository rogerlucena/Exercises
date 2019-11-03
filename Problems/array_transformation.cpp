#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

vector<int> transformArray(vector<int>& arr) {
	bool change = true;
	while(change) {
		change = false;
		vector<int> prevArr(arr);
		for(int i = 1; i < arr.size() - 1; ++i) {
			if(arr[i] > prevArr[i-1] && arr[i] > prevArr[i+1]) {
				--arr[i];
				change = true;
			} else if(arr[i] < prevArr[i-1] && arr[i] < prevArr[i+1]) {
				++arr[i];
				change = true;
			}
		}
	}

	return arr;
}

int main() {
	vector<int> arr = {2,1,2,1,1,2,2,1}; // ans expected: [2,2,1,1,1,2,2,1]
	cout << "Answer:" << endl;
	printVector(transformArray(arr));

	return 0;
}