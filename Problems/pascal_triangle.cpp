#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/pascal-triangle/

// Pascal Triangle

vector<int> generateRow(int r, const vector<int> &prevRow) {
	vector<int> ans = {1};
	for(int i = 0; i < r-2; i++) {
		ans.push_back(prevRow[i] + prevRow[i+1]);
	}
	ans.push_back(1);

	return ans;
}

vector<vector<int>> solve(int A) {
	vector<vector<int>> t = {};
	if(A == 0) {
		return t;
	}
	vector<int> r1 = {1};
	t.push_back(r1);
	if(A == 1) {
		return t;
	}
	for(int r = 2; r <= A; r++) {
		t.push_back(generateRow(r, t[r-2]));
	}
	return t;
}

int main() {
	printMatrix(solve(5));

	return 0;
}