#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// https://leetcode.com/problems/course-schedule/
// (topological sort is usually used when dealing with scheduling with dependencies, like here for example)
// Note: topo ordering has a <=> (if and only if) relation with existing no cycle in the directed graph!

// There are a total of n courses you have to take, labeled from 0 to n-1.
// Some courses may have prerequisites, for example to take course 0 you have to first take course 1, 
// which is expressed as a pair: [0,1]
// Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

// Example 1:
// Input: 2, [[1,0]] 
// Output: true
// Explanation: There are a total of 2 courses to take. 
//              To take course 1 you should have finished course 0. So it is possible.

// Example 2:
// Input: 2, [[1,0],[0,1]]
// Output: false
// Explanation: There are a total of 2 courses to take. 
//              To take course 1 you should have finished course 0, and to take course 0 you should
//              also have finished course 1. So it is impossible.

// Note: You may assume that there are no duplicate edges in the input prerequisites.
// Time: O(V+E) to build graph and O(V+E) to traverse, final = O(V+E).
// Space: O(V+E) for graph and O(V) for queue, final O(V+E).
bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
	// Edge v -> u if u depend on v (with TopoSort all the dependents will be to the right then - that is precisely what we want)
    vector<vector<int>> g(numCourses, vector<int>());
	vector<int> inDegree(numCourses, 0);
	for(vector<int> e : prerequisites) {
		g[e[1]].push_back(e[0]);
		++inDegree[e[0]];
	}

	// Property invariant for "q": a vertex only enters "q" if its current inDegree is 0 
	// (never happens for nodes in a cycle)  
	queue<int> q;
	for(int i = 0; i < numCourses; ++i) {
		if(inDegree[i] == 0) {
			q.push(i);
		}
	}

	int visitedCount = 0;
	// vector<int> topoOrdering;
	while(!q.empty()) {
		// If that vertex has current inDegree == 0, then it can now be pushed back into 
		// our virtual Topological Ordering without breaking any dependencies
		++visitedCount;
		int v = q.front();
		// topoOrdering.push_back(v); // if you want to have the ordering.
		q.pop();

		for(int neighbor : g[v]) {
            if (--inDegree[neighbor] == 0) {  // the ones that were 0 become negative now, so not enqueued again (similar to BFS with inDegree[i] == 0 representing the check to enqueue).
                q.push(neighbor);
            }
         }
	}
	
	return visitedCount == numCourses;
}

// Topological sort with DFS below (work if it is a DAG, does not verify if it is indeed a DAG <=> with no cycles)
void topologicalOrderingDFS(const vector<vector<int>> &g, int v, vector<bool> &visited, stack<int> &topoOrdering) {
	visited[v] = true;
	for(int neighbor : g[v]) {
		if(!visited[neighbor]) {
			topologicalOrderingDFS(g, neighbor, visited, topoOrdering);
		}
	}

	topoOrdering.push(v);
}

vector<int> possibleSchedulingOrder(int numCourses, vector<vector<int>> &prerequisites) {
    vector<vector<int>> g (numCourses, vector<int>());
	for(vector<int> e : prerequisites) {
		g[e[1]].push_back(e[0]);
	}

	vector<bool> visited (numCourses, false);
	stack<int> topoOrdering;
	for(int v = 0; v < numCourses; ++v) {
		if(!visited[v]) {
			topologicalOrderingDFS(g, v, visited, topoOrdering);
		}
	}

	vector<int> ans;
	while(!topoOrdering.empty()) {
		ans.push_back(topoOrdering.top());
		topoOrdering.pop();
	}
	
	return ans;
}

// To verify if a directed graph has cycles use topo sort with queue as above (simpler), or the adaptation
// of DFS below.
// Note: for verifying if cycle in undirected graph use BFS or DFS tracking "parent" as in __valid_tree.cpp 
// For directed graphs see the example: a -> b -> c and d -> b (b is visited from another DFS, but still we do not 
// have a cycle), so we need to keep recursion_stack[v] bools because only if visited in the current DFS we have
// a cycle, recursion_stack[v] is backtracked to false after visiting the neighbors during that DFS.
// Utility function for DFS to detect a cycle in a directed graph.
bool isCyclicUtil(vector<vector<int>> &g, int v, vector<bool>& visited, vector<bool>& rec_stack) {
    // Mark the current node as visited and add it to the recursion stack.
    visited[v] = true;
    rec_stack[v] = true;

    for (int neighbor : g[v]) {
		if (rec_stack[neighbor]) {
			return true;
		}
		if (!visited[neighbor] && isCyclicUtil(g, neighbor, visited, rec_stack)) {
			return true;
		}   
	}

    // Remove the node from the recursion stack ("current DFS").
    rec_stack[v] = false;
    return false;
}

// Function to detect cycle in a directed graph using DFS (from GeeksForGeeks).
bool isCyclicDFS(int n, vector<vector<int>> &edges) {
    vector<vector<int>> g(n);
    for(vector<int> e : edges) {
		g[e[1]].push_back(e[0]); // Arrow from e[1] to e[0] in this case as above for course dependencies.
	}

    // visited[] keeps track of all-time visited nodes.
    // recStack[] keeps track of nodes in the current recursion stack (current DFS).
    vector<bool> visited(n, false);
    vector<bool> rec_stack(n, false);

    // Check for cycles starting from every unvisited node.
    for (int i = 0; i < n; i++) {
        if (!visited[i] && isCyclicUtil(g, i, visited, rec_stack)) {
            return true; // Cycle found.
		}
    }

    return false; // No cycles detected.
}

int main() {
	int numCourses = 2;
	// vector<vector<int>> prerequisites = {{1, 0}}; // ans: 1
	vector<vector<int>> prerequisites = {{1, 0}, {0, 1}}; // ans: 0

	cout << "Answer: " << canFinish(numCourses, prerequisites) << endl;

	return 0;
}