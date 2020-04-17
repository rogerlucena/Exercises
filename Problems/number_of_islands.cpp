#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/number-of-islands/

// Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island 
// is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You 
// may assume all four edges of the grid are all surrounded by water.

// Example:
// Input:
// 11000
// 11000
// 00100
// 00011
// Output: 3

int islandFrom(vector<vector<char>> &grid, int i, int j) {
	grid[i][j] = '2'; // visited

	vector<vector<int>> ij = {{i+1, j}, {i-1, j}, {i, j+1}, {i, j-1}};
	for(vector<int> pos : ij) {
		if(pos[0] < 0 || pos[0] >= grid.size() || pos[1] < 0 || pos[1] >= grid[0].size()) {
			continue;
		}

		if(grid[pos[0]][pos[1]] == '1') {
			islandFrom(grid, pos[0], pos[1]);
		}
	}

	return 1;
}

int numIslands(vector<vector<char>> &grid) {
    int numOfIslands = 0;

	for(int i = 0; i < grid.size(); ++i) {
		for(int j = 0; j < grid[0].size(); ++j) {
			if(grid[i][j] == '1') {
				numOfIslands += islandFrom(grid, i, j);
			}
		}
	}

	return numOfIslands;
}

int main() {
	// vector<vector<char>> grid = {{'1','1','0','0','0'},
	// 							 {'1','1','0','0','0'},
	// 							 {'0','0','1','0','0'},
	// 							 {'0','0','0','1','1'}}; // ans: 3

	vector<vector<char>> grid = {{'1','1','1','1','1','1','1','1','1'},
								 {'1','0','0','0','0','0','0','0','1'},
								 {'1','0','1','0','1','0','1','0','1'},
								 {'1','0','1','0','1','0','1','0','1'},
								 {'1','0','1','0','1','0','1','0','1'},
								 {'1','0','0','0','0','0','0','0','1'},
								 {'1','1','1','1','1','1','1','1','1'}}; // ans: 4

	cout << "Answer: " << numIslands(grid) << endl;
	return 0;
}