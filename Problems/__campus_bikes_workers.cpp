#include <iostream>
#include <vector>
#include <queue>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/campus-bikes/

// On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M. 
// Each worker and bike is a 2D coordinate on this grid.

// Our goal is to assign a bike to each worker. Among the available bikes and workers, we choose the (worker, bike) 
// pair with the shortest Manhattan distance between each other, and assign the bike to that worker. (If there are multiple (worker, bike) 
// pairs with the same shortest Manhattan distance, we choose the pair with the smallest worker index; if there are multiple ways to do that, we 
// choose the pair with the smallest bike index). We repeat this process until there are no available workers.

// The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.
// Return a vector ans of length N, where ans[i] is the index (0-indexed) of the bike that the i-th worker is assigned to.

// Note:
// 0 <= workers[i][j], bikes[i][j] < 1000
// All worker and bike locations are distinct.
// 1 <= workers.length <= bikes.length <= 1000

// Key idea: use the distances as buckets, be attentive with the order you fill the buckets.
// The max distance is 2000!! Pay attention to the constraints of your problem.
// O(N * M) in time and space

int getDistance(const vector<int>& worker, const vector<int>& bike) {
	return abs(bike[0] - worker[0]) + abs(bike[1] - worker[1]);
}

vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
	vector<vector<pair<int, int>>> buckets(2000);
	for(int i = 0; i < workers.size(); ++i) {
		for(int j = 0; j < bikes.size(); ++j) {
			int d = getDistance(workers[i], bikes[j]);
			buckets[d].push_back({i, j});
		}
	}

	vector<int> assigned(workers.size(), -1);
	vector<bool> bikeUsed(bikes.size(), false);
	int nAssigned = 0;
	for(int i = 0; i < buckets.size(); ++i) {
		for(int j = 0; j < buckets[i].size(); ++j) {
			if(nAssigned == workers.size()) {
				return assigned;
			}
			int worker = buckets[i][j].first;
			int bike = buckets[i][j].second;
			if(assigned[worker] == -1 && bikeUsed[bike] == false) {
				assigned[worker] = bike;
				bikeUsed[bike] = true;
				++nAssigned;
			}
		}
	}

	return assigned;
}

auto cmp = [](const vector<int> &p1, const vector<int> &p2) {return p1[0] != p2[0] ? 
																		p1[0] > p2[0] : 
																		p1[1] != p2[1] ? 
																			p1[1] > p2[1] : 
																			p1[2] > p2[2];};

// being L = nWorkers * nBikes, then this is O(L log L)
// time limit exceed
vector<int> assignBikesPq(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
	priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> allCombinations(cmp, {});
	for(int i = 0; i < workers.size(); ++i) {
		for(int j = 0; j < bikes.size(); ++j) {
			int d = getDistance(workers[i], bikes[j]);
			allCombinations.push({d, i, j});
		}
	}

	vector<int> assigned(workers.size(), -1);
	vector<bool> bikeUsed(bikes.size(), false);
	int nAssigned = 0;
	while(nAssigned < workers.size()) {
		vector<int> combination = allCombinations.top();
		allCombinations.pop();
		int worker = combination[1];
		int bike = combination[2];
		if(assigned[worker] == -1 && bikeUsed[bike] == false) {
			assigned[worker] = bike;
			bikeUsed[bike] = true;
			++nAssigned;
		}
	}

	return assigned;
}

int main() {
	vector<vector<int>> workers = {{0, 0}, {1, 1}, {2, 0}};
	vector<vector<int>> bikes = {{1, 0}, {2, 2}, {2, 1}};

	printVector(assignBikesPq(workers, bikes)); // [0,2,1]

	return 0;
}

// Runtime: 152 ms, faster than 87.31% of C++ online submissions for Campus Bikes.
// Memory Usage: 44.3 MB, less than 33.70% of C++ online submissions for Campus Bikes.