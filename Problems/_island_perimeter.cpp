#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/island-perimeter
// https://leetcode.com/problems/island-perimeter

// You are given a row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
// Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and 
// there is exactly one island (i.e., one or more connected land cells).
// The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is
// a square with side length 1.
// Return the perimeter of the island.

// Example:
// Input: grid = [
//     [1,1,0,0],
//     [1,0,0,0],
//     [1,1,1,0],
//     [0,0,1,1]
// ]
// Output: 18

// Constraints:
// 1 <= row, col <= 100
// grid[i][j] is 0 or 1.
// There is exactly one island in grid.

// Remember: nice and different DFS count - good way to count perimeter transitions (name the function as "dfs", no problems).
// O(N * M) in time and space, but could stack overflow if huge grids/islands -> this way prefer the iterative way below (or the
// iterative BFS version of this).
int dfs(int i, int j, vector<vector<int>>& grid) {
	if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == 0) {
		return 1;
	}
	if (grid[i][j] == -1) {
		return 0;
	}
	grid[i][j] = -1;  // mark visited.
	
	return dfs(i + 1, j, grid) + dfs(i - 1, j, grid) + dfs(i, j + 1, grid) + dfs(i, j - 1, grid);
}

int islandPerimeter(vector<vector<int>>& grid) {
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[0].size(); ++j) {
			if (grid[i][j]) {
				return dfs(i, j, grid);
			}
		}
	}

	return 0;
}

// Checking each connection only once here compared to below (and subtracting 2 each time to remove that connection from
// the perimeter overcounted with +=4):
int islandPerimeterIterative(vector<vector<int>>& grid) {
	int m = grid.size(), n = grid[0].size();
	int res = 0;
	for (int r = 0; r < m; r++) {
		for (int c = 0; c < n; c++) {
			if (grid[r][c]) {
				res += 4;
				if (r && grid[r - 1][c]) {
					res -= 2;
				}
				if (c && grid[r][c - 1]) {
					res -= 2;
				}
			}
		}
	}
	return res;
}

// Or even simpler (but checking connections twice below):
int islandPerimeterIterativeSimpler(vector<vector<int>>& grid) {
	int m = grid.size(), n = grid[0].size(), res = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 1) {
				res += (i + 1 >= m || grid[i + 1][j] == 0) ? 1 : 0;
				res += (j + 1 >= n || grid[i][j + 1] == 0) ? 1 : 0;
				res += (i - 1 < 0 || grid[i - 1][j] == 0) ? 1 : 0;
				res += (j - 1 < 0 || grid[i][j - 1] == 0) ? 1 : 0;
			}
		}
	}
	return res;
}

int main() {
	cout << "Hello, World!";
	return 0;
}