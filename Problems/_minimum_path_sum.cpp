#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/minimum-path-sum/
// Interesting: Think top down instead of bottom up to use DP (key here), Dijkstra not necessary

// Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right 
// which minimizes the sum of all numbers along its path.

// Note: You can only move either down or right at any point in time. (impte isso aqui)

// Example:

// Input:
// [
//   [1,3,1],
//   [1,5,1],
//   [4,2,1]
// ]
// Output: 7
// Explanation: Because the path 1→3→1→1→1 minimizes the sum.

// DP solution
int minPathSum(vector<vector<int>> &grid) {
    if(grid.empty()) {
		return 0;
	}

	int r = grid.size();
	int c = grid[0].size();
	vector<vector<long>> minPath(r, vector<long>(c, LONG_MAX));
	minPath[0][0] = grid[0][0];

	for(int i = 1; i < grid.size(); ++i) {
		minPath[i][0] = minPath[i-1][0] + grid[i][0];
	}

	for(int j = 1; j < grid[0].size(); ++j) {
		minPath[0][j] = minPath[0][j-1] + grid[0][j];
	}

	for(int i = 1; i < grid.size(); ++i) {
		for(int j = 1; j < grid[0].size(); ++j) {
			minPath[i][j] = min(minPath[i-1][j], minPath[i][j-1]) + grid[i][j];
		}
	}

	return (int) minPath[r-1][c-1];
}


// ---
inline int getNodeValue(int i, int j, int nc) {
	return i * nc + j;
}

int getGridValueForNode(int neigh, const vector<vector<int>> &grid) {
	int nc = grid[0].size();
	int i = neigh / nc;
	int j = neigh % nc;

	return grid[i][j];
}

// Solution with "Dijkstra"
int minPathSumDijkstra(vector<vector<int>> &grid) {
	if(grid.empty()) {
		return 0;
	}

	int nr = grid.size(), nc = grid[0].size();
	unordered_map<int, long> open;

	vector<pair<int,long>> distancesVector;
	for(int i = 0; i < nr; ++i) {
		for(int j = 0; j < nc; ++j) {
			int nodeValue = getNodeValue(i, j, nc);
			open[nodeValue] = LONG_MAX;
			distancesVector.push_back({nodeValue, LONG_MAX});
		}
	}

	distancesVector[0].second = grid[0][0];
	open[0] = grid[0][0];
	auto cmp = [](pair<int,long> n1, pair<int,long> n2) {return n1.second > n2.second;};
    priority_queue<pair<int,long>, vector<pair<int,long>>, decltype(cmp)> distancesMinHeap(cmp, distancesVector);
	
	while(!open.empty()) {
		pair<int, long> node = distancesMinHeap.top();
		distancesMinHeap.pop();
		int nodeVal = node.first;

		if(open.find(nodeVal) == open.end()) {
			continue;
		}

		open.erase(nodeVal);
		long d = node.second;
		
		if(nodeVal == nr * nc - 1) {
			return d;
		}

		vector<int> neighbors;
		if(nodeVal % nc < nc - 1) {
			neighbors.push_back(nodeVal + 1);
		}
		if(nodeVal / nc < nr - 1) {
			neighbors.push_back(nodeVal + nc);
		}

		for(int neigh : neighbors) {
			long neighDistance = d + getGridValueForNode(neigh, grid);
			if(open.find(neigh) != open.end() && neighDistance < open[neigh]) {
				open[neigh] = neighDistance;
				distancesMinHeap.push({neigh, neighDistance});
			}
		}

	}

	return 0;
}

int main() {
	vector<vector<int>> grid = {{1,3,1},
  								{1,5,1},
  								{4,2,1}}; // ans: 7
	
	cout << "Answer: " << minPathSum(grid) << endl;
	return 0;
}



// Trying a bottom-up rec solution
// void minPathSumFrom(const vector<vector<int>> &grid, vector<vector<long>> &minPath, 
// 					int i, int j, long currSum) {
// 	minPath[i][j] = currSum;

// 	vector<vector<int>> nextPos = {{i+1, j}, {i, j+1}};
// 	for(vector<int> pos : nextPos) {
// 		if(pos[0] >= grid.size() || pos[1] >= grid[0].size()) {
// 			continue;
// 		}

// 		int nextSum = currSum + grid[pos[0]][pos[1]];
// 		if(nextSum < minPath[pos[0]][pos[1]]) {
// 			minPathSumFrom(grid, minPath, pos[0], pos[1], nextSum);
// 		}
// 	}
// }

// int minPathSum(vector<vector<int>> &grid) {
//     if(grid.empty()) {
// 		return 0;
// 	}

// 	int r = grid.size();
// 	int c = grid[0].size();
// 	vector<vector<long>> minPath(r, vector<long>(c, LONG_MAX));
// 	minPathSumFrom(grid, minPath, 0, 0, grid[0][0]);

// 	return (int) minPath[r-1][c-1];
// }