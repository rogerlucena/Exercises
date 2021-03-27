#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

// https://www.pramp.com/challenge/Y56aZmaj9Ptmd9wV9xvL

// In a given grid of 0s and 1s, we have some starting row and column sr, sc and a target row and column tr, tc.
// Return the length of the shortest path from sr, sc to tr, tc that walks along 1 values only.

// Each location in the path, including the start and the end, must be a 1. Each subsequent location in the path must be
// 4-directionally adjacent to the previous location.

// It is guaranteed that grid[sr][sc] = grid[tr][tc] = 1, and the starting and target positions are different.

// If the task is impossible, return -1.

// Example:
// input:
// grid = [[1, 1, 1, 1], [0, 0, 0, 1], [1, 1, 1, 1]]
// sr = 0, sc = 0, tr = 2, tc = 0
// output: 8
// (The lines below represent this grid:)
// 1111
// 0001
// 1111

// Attention! Min path is always BFS, DFS will not work here! (vacilou quando pensou em DFS primeiro!)
// Use Dijkstra only if weighted graph (and non-negative edges).
int getCode(int row, int column, int nCols) {
	return row * nCols + column;
}

bool isValid(const vector<vector<int>>& grid, int r, int c) {
	return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
}

int shortestCellPath(const vector<vector<int>>& grid, int sr, int sc, int tr, int tc) {
	int nCols = grid[0].size();
	unordered_set<int> enq;
	queue<vector<int>> q;
	q.push({sr, sc, 0});
	enq.insert(getCode(sr, sc, nCols));

	while (!q.empty()) {
		vector<int> posD = q.front();
		q.pop();
		int r = posD[0];
		int c = posD[1];
		int d = posD[2];
		if (r == tr && c == tc) {
			return d;
		}

		vector<vector<int>> neighbors = {{r+1, c}, {r-1, c}, {r, c-1}, {r, c+1}};
		for (vector<int> neigh : neighbors) {
			int nR = neigh[0];
			int nC = neigh[1];
			if (!isValid(grid, nR, nC) || !grid[nR][nC] || enq.find(getCode(nR, nC, nCols)) != enq.end()) {
				continue;
			}
			q.push({nR, nC, d+1});
			enq.insert(getCode(nR, nC, nCols));
		}
	}
	
	return -1;
}

int main() {
	vector<vector<int>> grid = {{1,1,1,1},
								{1,0,0,1},
								{1,1,1,1}}; // ans: 2
	int sr = 0, sc = 0, tr = 0, tc = 2;

	int ans = shortestCellPath(grid, sr, sc, tr, tc);
	cout << "Answer: " << ans << endl;
	
	return 0;
}