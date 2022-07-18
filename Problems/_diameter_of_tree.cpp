#include <iostream>
#include <vector>
#include <unordered_map>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/contest/biweekly-contest-12/problems/tree-diameter/

// Given an undirected tree, return its diameter: the number of edges in a longest path in that tree.
// The tree is given as an array of edges where edges[i] = [u, v] is a bidirectional edge 
// between nodes u and v.  Each node has labels in the set {0, 1, ..., edges.length}.

void printGraph(unordered_map<int, vector<int>> &g) {
	for(pair<int, vector<int>> p : g) {
		cout << "Node: " << p.first << endl;
		printVector(p.second);
	}
}

// using only "parent" because we are in a tree, if it was an actual graph we should use hash set "visited".
pair<int, int> dfs(int n, unordered_map<int, vector<int>> &g, int parent) {
	int maxDistance = 0;
	int farthestNode = n;
	pair<int, int> ans = {maxDistance, farthestNode};

	for(int neigh : g[n]) {
		if(neigh != parent) {
			pair<int, int> dfsFromNeighbor = dfs(neigh, g, n);
			if(ans.first < dfsFromNeighbor.first + 1) {
				ans.first = dfsFromNeighbor.first + 1;
				ans.second = dfsFromNeighbor.second;
			} 
		}
	}

	return ans;
}

// Obs: case of empty edges, resulting in an empty graph, is handled by g[n] above returning an empty vector. If
// using g.at(n) as below (to use const ref for the graph) we have an error and then we need to handle this case as a separate if (as below).
int treeDiameter(vector<vector<int>> &edges) {
	unordered_map<int, vector<int>> g;
	for(vector<int> e : edges) {
		g[e[0]].push_back(e[1]);
		g[e[1]].push_back(e[0]);
	}

	// printGraph(g);

	pair<int, int> ans = dfs(0, g, -1);
	ans = dfs(ans.second, g, -1);

	return ans.first;
}

/*
pair<int, int> GetFarthestFrom(int n, const unordered_map<int, vector<int>>& g, unordered_set<int>& visited) {
	pair<int, int> farthest = {n, 0};
	visited.insert(n);
	for (int neigh : g.at(n)) {
	if (visited.find(neigh) != visited.end()) {
		continue;
	}
	pair<int, int> farthest_from_neigh = GetFarthestFrom(neigh, g, visited);
	if (farthest_from_neigh.second + 1 > farthest.second) {
		// farthest = farthest_from_neigh;
		// farthest = make_pair<int, int>(int(farthest_from_neigh.first), farthest_from_neigh.second + 1);
		farthest.first = farthest_from_neigh.first;
		farthest.second = farthest_from_neigh.second + 1;
	}
	}

	return farthest;
}

int treeDiameter(vector<vector<int>>& edges) {
	if (edges.empty()) {
	return 0;
	}
	unordered_map<int, vector<int>> g;
	for (const vector<int>& e : edges) {
	g[e[0]].push_back(e[1]);
	g[e[1]].push_back(e[0]);
	}

	unordered_set<int> visited;
	pair<int, int> farthest = GetFarthestFrom(0, g, visited);
	visited.clear();
	pair<int, int> ans = GetFarthestFrom(farthest.first, g, visited);

	return ans.second;
}
*/

int main() {
	// vector<vector<int>> edges = {{0,1},{0,2}}; // ans expected: 2
	vector<vector<int>> edges = {{0,1},{0,2},{2,3},{2,4},{2,5},{4,6},{0,7},{0,8},{3,9},
								{8,10},{8,11},{2,12},{7,13},{4,14},{12,15},{13,16},{14,17},
								{11,18},{18,19},{16,20},{2,21},{4,22},{9,23},{1,24},{4,25},
								{15,26},{19,27},{2,28},{16,29},{9,30},{21,31},{13,32},{5,33},
								{9,34},{2,35},{17,36},{1,37},{33,38},{0,39},{18,40},{29,41},
								{1,42},{37,43},{13,44},{19,45},{3,46},{1,47},{18,48}}; // ans expected: 10
	
	cout << "Answer: " << treeDiameter(edges) << endl;
	return 0;
}