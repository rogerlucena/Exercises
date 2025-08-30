#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

// https://neetcode.io/problems/valid-tree
// https://leetcode.com/problems/graph-valid-tree
// Remember: topo sort is for *directed_ graphs* (indegrees), for undirected ones think about simple 
// DFS/BFS (keeping track of the "parent" to not "come back" if checking if it has no cycles as here) or even Union-Find!
// Remember: tracking "parent" is useful for undirected graphs, when trying to check for cycles, if directed
// graphs the normal DFS will do the job checking "rec_stack" and "visited" before jumping to 
// "neighbor" (see __course_schedule_dependencies.cpp) - or preferably doing topo sort with queue (simpler).
// Remember: practice remember DFS, BFS, and Union-Find below.

// Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to 
// check whether these edges make up a valid tree.

// Example 1:
// Input:
// n = 5
// edges = [[0, 1], [0, 2], [0, 3], [1, 4]]
// Output:
// true

// Note:
// You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same 
// as [1, 0] and thus will not appear together in edges.

// Constraints:
// 1 <= n <= 100
// 0 <= edges.length <= n * (n - 1) / 2

// DFS:
bool dfsFoundCycle(const vector<vector<int>>& g, int node, int parent, unordered_set<int>& visited) {
    visited.insert(node);
    for (int neighbor : g[node]) {
        if (neighbor == parent) {
            continue;
        }
        if (visited.count(neighbor)) {
            return true;
        }
        if (dfsFoundCycle(g, neighbor, node, visited)) {
            return true;
        }
    }

    return false;
}

bool validTree(int n, vector<vector<int>>& edges) {
    if (edges.size() != n - 1) {
        return false;
    }

    vector<vector<int>> g(n);
    for (const vector<int>& e : edges) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }

    unordered_set<int> visited;
    if (dfsFoundCycle(g, 0, -1, visited)) {
        return false;
    }

    // return visited.size() == n; // not needed because if #edges = n-1 and we have no cycles we necessarily have a tree, use this if not checking #edges == n-1 before (generic case of not only one tree).
    return true;
}
// If not only one tree, do a "for" over the vertices and call DFS if not already visited (for undirected graphs) - from GeeksForGeeks:
// for (int v = 0; v < n; ++v) {
//     if (!visited[v]) {
//         if (dfsFoundCycle(g, v, -1, visited))
//             return true;
//     }
// }
// But for directed graphs we also need to keep recursion_stack[v] bools because only if visited in the current DFS we have
// a cycle, recursion_stack[v] is backtracked to false after visiting the neighbors during that DFS.
// For directed graphs see the example: a -> b -> c and d -> b (b is visited from another DFS, but still we do not 
// have a cycle), that is why we need recursion_stack[v] there, see complete code in __course_schedule_dependencies.cpp

// BFS:
bool validTreeBFS(int n, vector<vector<int>>& edges) {
    if (edges.size() != n - 1) {
        return false;
    }

    vector<vector<int>> g(n);
    for (const vector<int>& e : edges) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }

    unordered_set<int> enqueued;
    queue<pair<int, int>> q;
    q.push({0, -1});
    enqueued.insert(0);
    while (!q.empty()) {
        auto [node, parent] = q.front();
        q.pop();
        for (int neighbor : g[node]) {
            if (neighbor == parent) {
                continue;
            }
            if (enqueued.count(neighbor)) {
                return false; // found a cycle.
            }
            q.push({neighbor, node});
            enqueued.insert(neighbor);
        }
    }

    // return enqueued.size() == n; // no need again as above, use this if not checking #edges == n-1 before (generic case of not only one tree).
    return true;
}

// Union-Find:
// Complexity: O(α(N)) ~ O(1) amortized with path compression and union by rank/size for both methods, where α is the Inverse-Ackermann function (function which value goes very very slowly).
// If only path compression, it seems that the complexity for each method becomes O(log n) - Princeton https://stackoverflow.com/questions/56229760/what-is-the-complexity-of-path-compression-technique-for-disjoint-set-algorithm
// Otherwise, if neither path compression nor union by rank/size it is linear O(N) worst case for both methods.
int Find(int v, vector<int>& parent) {
    if (parent[v] != v) {
        parent[v] = Find(parent[v], parent); // path compression.
    }

    return parent[v];
}

bool Union(int u, int v, vector<int>& parent) {
    int rep_u = Find(u, parent);
    int rep_v = Find(v, parent);
    if (rep_u == rep_v) {
        return false;
    }

    parent[rep_u] = rep_v;
    return true;
}

// Complexity in time: O(V + E.α(V)) if using path compression and union by rank -> O(V + E) amortized.
// Worst case Union/Find have both linear complexities if not using path compression and union by rank.
bool validTreeUnionFind(int n, vector<vector<int>>& edges) {
    if (edges.size() != n - 1) {
        return false;
    }

    vector<int> parent(n);
    for (int i = 0; i < parent.size(); ++i) { // O(V)
        parent[i] = i;
    }

    for (const vector<int>& e : edges) { // O(E.α(V))
        if (!Union(e[0], e[1], parent)) {
            return false; // has cycle in the undirected graph.
        }
    }

    // Use this if not checking #edges == n-1 before (generic case of not only one tree):
    // for (int i = 1; i < n; ++i) { // check if everyone is in the same group (only one connected component) - but not needed since #edges = n-1 and has no cycles.
    //     if (Find(i, parent) != Find(i - 1, parent)) { // remember to use Find here, and not just compare "parents" since not necessarily all were already path compressed.
    //         return false;
    //     }
    // }

    return true;
}

int main() {
	cout << "Hello, World!";
	return 0;
}