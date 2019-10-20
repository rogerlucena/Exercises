#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

vector<vector<int>> prettyPrint(int A) {
	int ansSize = 2 * A - 1; 
	vector<vector<int>> ans (ansSize, vector<int>(ansSize, 0));
	// printMatrix(ans);

	for(int i = 0; i < A; ++i) {
		int value = A - i;
		for(int r = i; r < ansSize-i; ++r) {
			ans[r][i] = value;
			ans[r][ansSize-1-i] = value;
		}
		for(int c = i; c < ansSize-i; ++c) {
			ans[i][c] = value;
			ans[ansSize-1-i][c] = value;
		}
	}

	return ans;
}


int main() {
	printMatrix(prettyPrint(4));
	return 0;
}