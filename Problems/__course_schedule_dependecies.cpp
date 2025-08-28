#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// https://leetcode.com/problems/course-schedule/
// (topological sort is usually used when dealing with scheduling with dependencies, like here for example)

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
			 if(--inDegree[neighbor] == 0) { // the ones that were 0 become negative now, so not visited again.
				 q.push(neighbor);
			 }
		 }
	}
	
	return visitedCount == numCourses;
}

// Topological sort with DFS below (work if it is a DAG, does not verify if it is indeed a DAG - with no cycles)
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

int main() {
	int numCourses = 2;
	// vector<vector<int>> prerequisites = {{1, 0}}; // ans: 1
	vector<vector<int>> prerequisites = {{1, 0}, {0, 1}}; // ans: 0

	cout << "Answer: " << canFinish(numCourses, prerequisites) << endl;

	return 0;
}