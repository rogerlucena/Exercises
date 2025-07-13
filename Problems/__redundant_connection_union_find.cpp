#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/redundant-connection/
// Classic example of Union-Find.
// A boolean DFS(source, target, visited) auxiliar function would have also worked (return true if reaches target from source).
// Complexity for running a DFS after taking each edge above: O(N^2) in time and O(N) is space.
// Complexity for Union-Find with path compression and union by rank: O(N) in space and O(N.α(N)) ≈ O(N) in time, where α is the Inverse-Ackermann function (function which value goes very very slowly).
// (it can be shown that the optmized Union above takes amortized O(α(N)) time, and that O(α(N)) is approximately O(1))

// In this problem, a tree is an undirected graph that is connected and has no cycles.

// -- Problem:
// You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added
// edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as
// an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.

// Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return
// the answer that occurs last in the input.

// Example:
// Input: edges = [[1,2],[1,3],[2,3]]
// Output: [2,3]

// Constraints:
// n == edges.length
// 3 <= n <= 1000
// edges[i].length == 2
// 1 <= ai < bi <= edges.length
// ai != bi
// There are no repeated edges.
// The given graph is connected.

int Find(unordered_map<int, int>& parent, int a) {
	if(parent.find(a) == parent.end()) {
		parent[a] = a;
	} else if (parent[a] != a) {
		parent[a] = Find(parent, parent[a]);
	}

	return parent[a];
}

void Union(unordered_map<int, int>& parent, int a, int b) {
	parent[Find(parent, a)] = Find(parent, b);
}

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
	unordered_map<int, int> parent;
	for (const vector<int>& edge : edges) {
		if (Find(parent, edge[0]) == Find(parent, edge[1])) {
			return edge;
		}
		Union(parent, edge[0], edge[1]);
	}

	return {};
}

int main() {
	vector<vector<int>> edges = {{1,2},{1,3},{2,3}};
	vector<int> ans = findRedundantConnection(edges);
	cout << ans[0] << ", " << ans[1] << endl;
	return 0;
}