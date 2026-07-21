#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/surrounded-regions
// https://leetcode.com/problems/surrounded-regions
// Remember: for the DFS solution it is a nice idea to start from the borders and mark the connected cells as persistant before the final pass.
// Nice to practice DFS and Union-Find below.

// You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:
// Connect: A cell is connected to adjacent cells horizontally or vertically.
// Region: To form a region connect every 'O' cell. Regions can have any shape; they do not need to be squares or rectangles.
// Surround: A region is surrounded if none of the 'O' cells in that region are on the edge of the board. Such regions are 
// completely enclosed by 'X' cells.
// To capture a surrounded region, replace all 'O's with 'X's in-place within the original board. You do not need to return anything.

// Example:
// Input: board = [
//   ["X","X","X","X"],
//   ["X","O","O","X"],
//   ["X","X","O","X"],
//   ["X","O","X","X"]
// ]

// Output: [
//   ["X","X","X","X"],
//   ["X","X","X","X"],
//   ["X","X","X","X"],
//   ["X","O","X","X"]
// ]

void dfs(int i, int j, vector<vector<char>>& board, const int r, const int c, const vector<vector<int>>& dir) {
	if (i < 0 || j < 0 || i >= r || j >= c || board[i][j] == 'X' || board[i][j] == 'S') {
		return;
	}
	board[i][j] = 'S';  // mark visited (and that it will "stay" as sand till the end).

	for (const vector<int>& d : dir) {
		dfs(i + d[0], j + d[1], board, r, c, dir);
	}
}

// O(m * n) in time and space (potential size of the recursion stack).
void solve(vector<vector<char>>& board) {
	const int r = board.size();
	const int c = board[0].size();
	const vector<vector<int>> dir = {{+1, 0}, {-1, 0}, {0, +1}, {0, -1}};

	for (int j = 0; j < c; ++j) {
		dfs(0, j, board, r, c, dir);
		dfs(r - 1, j, board, r, c, dir);
	}
	for (int i = 1; i < r - 1; ++i) {
		dfs(i, 0, board, r, c, dir);
		dfs(i, c - 1, board, r, c, dir);
	}

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			if (board[i][j] == 'O') {
				board[i][j] = 'X';
			} else if (board[i][j] == 'S') {
				board[i][j] = 'O';
			}
		}
	}
}

// Practice Union-Find (more complex and verbose solution below):
int findUtil(int u, vector<int>& parent) {
	if (parent[u] != u) {
		parent[u] = findUtil(parent[u], parent); 
	}

	return parent[u];
}

void unionUtil(int u, int v, vector<int>& parent, vector<int>& rank) {
	int rep_u = findUtil(u, parent);
	int rep_v = findUtil(v, parent);

	if (rep_u == rep_v) {
		return;
	}

	if (rank[rep_u] < rank[rep_v]) {
		parent[rep_u] = rep_v;
	} else if (rank[rep_u] > rank[rep_v]) {
		parent[rep_v] = rep_u;
	} else {
		parent[rep_u] = rep_v;
		++rank[rep_v];
	}
}

inline int getID(int i, int j, int c) {  // modern C++ compilers would probably already automatically inline these small functions repeatedely called, so the "inline" keyword is optional here (but maybe worthy mentioning during the interview to show you know it, as a keyword historically used to "hint" the compiler to already inline it).
	return j + i * c;
}

inline bool isBorder(int i, int j, int r, int c) {
	return i == 0 || i == r - 1 || j == 0 || j == c - 1;
}

void solveUnionFind(vector<vector<char>>& board) {
	const int r = board.size();  // nice to use const for variables like these during the interview (shows defensive coding and maturity).
	const int c = board[0].size();
	const int edge = r * c;  // dummy representative of the family of cells connected to the edge.
	
	vector<int> parent(r * c + 1);
	vector<int> rank(r * c + 1, 1);

	for (int i = 0; i < parent.size(); ++i) {
		parent[i] = i;
	}

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			if (board[i][j] == 'X') {
				continue;
			}
			int ij_id = getID(i, j, c);
			if (isBorder(i, j, r, c)) {
				unionUtil(ij_id, edge, parent, rank);  // if checking only the border above and to the left as below (for simplicity and less code) you cannot write "continue;" here because the last row and the last column (that are "edge") should union to the cells above and to the left of them too.
			}
			if (i && board[i - 1][j] == 'O') {
				unionUtil(ij_id, getID(i - 1, j, c), parent, rank);
			}
			if (j && board[i][j - 1] == 'O') {
				unionUtil(ij_id, getID(i, j - 1, c), parent, rank);
			}
		}
	}

	int rep_edge = findUtil(edge, parent);
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			if (board[i][j] == 'O' && findUtil(getID(i, j, c), parent) != rep_edge) {
				board[i][j] = 'X';
			}
		}
	}
}

int main() {
	cout << "Hello, World!";
	return 0;
}