#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// https://leetcode.com/problems/rotting-oranges
// https://neetcode.io/problems/rotting-fruit
// Remember: BFS by levels starting with all the rotten oranges in the queue at
// level 0 (levels are "distances" - understood as time here).

// You are given an m x n grid where each cell can have one of three values:

// 0 representing an empty cell,
// 1 representing a fresh orange, or
// 2 representing a rotten orange.
// Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

// Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

// Example:
// Input: grid = [[2,1,1],
//                [1,1,0],
//                [0,1,1]]
// Output: 4

// Constraints:
// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 10
// grid[i][j] is 0, 1, or 2.

// O(m * n) in time and space.
int orangesRotting(vector<vector<int>>& grid) {
    int ROWS = grid.size();
    int COLS = grid[0].size();
    int n_fresh = 0;
    queue<pair<int, int>> q;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (grid[i][j] == 2) {
                q.push({i, j});
            } else if (grid[i][j] == 1) {
                ++n_fresh;
            }
        }
    }

    int t = 0;
    vector<pair<int, int>> directions({{+1, 0}, {-1, 0}, {0, +1}, {0, -1}});
    while (!q.empty() && n_fresh > 0) {
        int len = q.size();
        for (int rep = 1; rep <= len; ++rep) {
            pair<int, int> curr = q.front();
            q.pop();
            for (const pair<int, int>& dir : directions) {
                int n_i = curr.first + dir.first;  // neighbor i.
                int n_j = curr.second + dir.second;  // neighbor j.
                if (n_i < 0 || n_i >= ROWS || n_j < 0 || n_j >= COLS) {
                    continue;
                }
                if (grid[n_i][n_j] == 1) {
                    q.push({n_i, n_j});
                    grid[n_i][n_j] = 2;  // here, being rotten also flags that position as already enqueued (to not enqueue twice).
                    --n_fresh;
                }
            }
        }
        ++t;
    }

    return n_fresh == 0 ? t : -1;
}

int main() {
	cout << "Hello, World!";
	return 0;
}