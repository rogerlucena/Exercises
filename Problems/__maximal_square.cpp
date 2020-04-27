#include <iostream>
#include <vector>
#include <string>

using namespace std;

// https://leetcode.com/problems/maximal-square/
// Just think about filling the beginning of the matrix and, from that, build your dp solution!

// Given a 2D binary matrix filled with 0's and 1's, find the largest square containing 
// only 1's and return its area.

int maximalSquare(vector<vector<char>> &matrix) {
	if (matrix.empty()) {
		return 0;
	}

	int maxSide = 0;
	int r = matrix.size();
	int c = matrix[0].size();
	vector<vector<int>> dp(r, vector<int>(c, 0));

	for (int i = 0; i < r; ++i) {
		dp[i][0] = (matrix[i][0] == '1' ? 1 : 0);
		maxSide = max(maxSide, dp[i][0]);
	}

	for (int j = 0; j < c; ++j) {
		dp[0][j] = (matrix[0][j] == '1' ? 1 : 0);
		maxSide = max(maxSide, dp[0][j]);
	}

	for (int i = 1; i < r; ++i) {
		for (int j = 1; j < c; ++j) {
			dp[i][j] = (matrix[i][j] == '0' ? 0 : min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1);
			maxSide = max(maxSide, dp[i][j]);
		}
	}

	return maxSide * maxSide;
}

int main() {
	// vector<vector<char>> matrix = {{'1','0','1','0','0'},
	// 							   {'1','0','1','1','1'},
	// 							   {'1','1','1','1','1'},
	// 							   {'1','0','0','1','0'}}; // ans: 4

	vector<vector<char>> matrix = {{'1','1','1','1','1','1','1','1'},
								   {'1','1','1','1','1','1','1','0'},
		                           {'1','1','1','1','1','1','1','0'},
								   {'1','1','1','1','1','0','0','0'},
								   {'0','1','1','1','1','0','0','0'}}; // ans: 16

	cout << "Answer: " << maximalSquare(matrix) << endl;

	return 0;
}