#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// https://neetcode.io/problems/count-connected-components
// https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph  
// Remember: for normal DFS in undirected graph as here there is no need to keep track of "parent" since not 
// checking cycles and "parent" will already be marked visited and then skipped (no infinite loop).
// Also solved with Union-Find below.

// There is an undirected graph with n nodes. There is also an edges array, where edges[i] = [a, b] means that 
// there is an edge between node a and node b in the graph.
// The nodes are numbered from 0 to n - 1.
// Return the total number of connected components in that graph.

// Example:
// Input:
// n=6
// edges=[[0,1], [1,2], [2,3], [4,5]]
// Output:
// 2

// DFS:
void dfs(int node, const vector<vector<int>>& g, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor: g[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, g, visited);
        }
    }
}

int countComponents(int n, vector<vector<int>>& edges) {
    vector<vector<int>> g(n);
    for (const vector<int>& e : edges) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }

    vector<bool> visited(n, false);
    int n_components = 0;
    for (int node = 0; node < n; ++node) {
        if (!visited[node]) {
            dfs(node, g, visited);
            ++n_components;
        }
    }

    return n_components;
}

// Union-Find:
// Each method will be O(α(V)) in time which is ~O(1) amortized given that I used both path compression
// and union by rank optimizations here (where α is the Inverse-Ackermann function - function which value goes very very slowly).
int Find(int v, vector<int>& parent) {
    if (parent[v] != v) {
        parent[v] = Find(parent[v], parent); // Path compression.
    }

    return parent[v];
}

void Union(int u, int v, vector<int>& parent, vector<int>& rank) { // Union by rank.
    int rep_u = Find(u, parent);
    int rep_v = Find(v, parent);
    if (rep_u == rep_v) {
        return;
    }
    if (rank[rep_u] < rank[rep_v]) {
        parent[rep_u] = rep_v;
    } else if (rank[rep_u] > rank[rep_v]) {
        parent[rep_v] = rep_u;
    } else {
        // Same rank, make one root and increase its rank.
        parent[rep_v] = rep_u;
        ++rank[rep_u];
    }
}

int countComponentsUnionFind(int n, vector<vector<int>>& edges) {
    vector<int> rank(n, 0);
    vector<int> parent(n);
    for (int i = 0; i < parent.size(); ++i) {
        parent[i] = i;
    }

    for (const vector<int>& e : edges) {
        Union(e[0], e[1], parent, rank);
    }

    unordered_set<int> representatives;
    for (int node = 0; node < n; ++node) {
        representatives.insert(Find(node, parent));
    }

    return representatives.size();
}

int main() {
	cout << "Hello, World!";
	return 0;
}