#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

https://leetcode.com/problems/max-area-of-island/

// Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected
// 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
// Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)

// Could improve memory: no need of "visited", just mark that land as water after visiting.
inline int getCode(int i, int j, int nCols) {
	return i * nCols + j;
}

int getIslandFrom(int i, int j, const vector<vector<int>>& grid, unordered_set<int>& visited) {
	int area = 1;
	int code = getCode(i, j, grid[0].size());
	visited.insert(code);
	vector<vector<int>> newPos = {{i+1, j}, {i-1, j}, {i, j-1}, {i, j+1}};
	for(vector<int> pos : newPos) {
		int r = pos[0];
		int c = pos[1];
		int newCode = getCode(r, c, grid[0].size());
		if(r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || !grid[r][c] || visited.find(newCode) != visited.end()) {
			continue;
		}
		area += getIslandFrom(r, c, grid, visited);
	}

	return area;
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
	if(grid.empty()) {
		return 0;
	}

	unordered_set<int> visited;
	int maxIsland = 0;
	for(int i = 0; i < grid.size(); ++i) {
		for(int j = 0; j < grid[0].size(); ++j) {
			int code = getCode(i, j, grid[0].size());
			if(grid[i][j] && visited.find(code) == visited.end()) {
				maxIsland = max(maxIsland, getIslandFrom(i, j, grid, visited));
			}
		}
	}

	return maxIsland;
}

int main() {
	vector<vector<int>> grid = {{0,0,1,0,0,0,0,1,0,0,0,0,0},
								{0,0,0,0,0,0,0,1,1,1,0,0,0},
								{0,1,1,0,1,0,0,0,0,0,0,0,0},
								{0,1,0,0,1,1,0,0,1,0,1,0,0},
								{0,1,0,0,1,1,0,0,1,1,1,0,0},
								{0,0,0,0,0,0,0,0,0,0,1,0,0},
								{0,0,0,0,0,0,0,1,1,1,0,0,0},
								{0,0,0,0,0,0,0,1,1,0,0,0,0}}; // ans: 6

	int ans = maxAreaOfIsland(grid);
	cout << "Answer: " << ans << endl;

	return 0;
}