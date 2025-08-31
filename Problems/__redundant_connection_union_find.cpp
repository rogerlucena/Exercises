#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/redundant-connection/
// Classic example of Union-Find.
// A boolean DFS(source, target, visited) auxiliar function would have also worked (return true if reaches target from source).
// Complexity for running a DFS after taking each edge above: O(N^2) in time and O(N) is space.
// A boolean DFS(node, parent, visited) function could have also worked (return true if reaches already visited node, keeping track of parent since undirected graph to not "come back from where it came", see __valid_tree.cpp for how to check for cycle in undirected graph using DFS).

// Remember:
// Complexity for Union-Find with path compression and union by rank/size: O(N) in space and O(N.α(N)) ≈ O(N) in time, where α is the Inverse-Ackermann function (function which value goes very very slowly) - think of it as amortized.
// (it can be shown that the optimized Find and Union methods with path compression and union by rank takes amortized O(α(V)) time, and that O(α(V)) is approximately O(1)) - amortized.
// Worst case Union/Find have both linear complexities if not using path compression and union by rank/size.
// For Union-Find with only path compression and not union by rank/size it seems the complexity for each method becomes O(log V) (already better than linear) - Princeton https://stackoverflow.com/questions/56229760/what-is-the-complexity-of-path-compression-technique-for-disjoint-set-algorithm

// In this problem, a tree is an *undirected graph* that is connected and has no cycles.

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

int Find(int v, vector<int>& parent) {
    if (parent[v] != v) {
        parent[v] = Find(parent[v], parent);  // path compression.
    }

    return parent[v];
}

void Union(int u, int v, vector<int>& parent, vector<int>& rank) {  // union by rank.
    int rep_u = Find(u, parent);
    int rep_v = Find(v, parent);
    if (rep_u == rep_v) {
        return;
    }
    if (rank[rep_u] < rank[rep_v]) {
        parent[rep_u] = rep_v;
    } else if (rank[rep_u] > rank[rep_v]) {
        parent[rep_v] = rep_u;
    } else { // same rank, choose one as root and increment its rank then.
        parent[rep_v] = rep_u;
        ++rank[rep_u];
    }
}

void UnionWithoutByRank(int u, int v, vector<int>& parent) {
    int rep_u = Find(u, parent);
    int rep_v = Find(v, parent);
    parent[rep_u] = rep_v;  // if rep_u == rep_v nothing is changed.
}

int FindWithNotInitializedHashMap(int a, unordered_map<int, int>& parent) {
	if(parent.find(a) == parent.end()) {
		parent[a] = a;
	} else if (parent[a] != a) {
		parent[a] = FindWithNotInitializedHashMap(parent[a], parent);
	}

	return parent[a];
}

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();  // nodes from 1 to n.
    vector<int> rank(n + 1, 0);
    vector<int> parent(n + 1);
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }

    for (const vector<int>& e : edges) {  // O(N*alpha(N)) on Leetcode complexity result using both path compression and union by rank.
        if (Find(e[0], parent) == Find(e[1], parent)) {
            return e;
        }
        Union(e[0], e[1], parent, rank);
    }

    return {};
}

int main() {
	vector<vector<int>> edges = {{1,2},{1,3},{2,3}};
	vector<int> ans = findRedundantConnection(edges);
	cout << ans[0] << ", " << ans[1] << endl;
	return 0;
}