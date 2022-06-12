#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/evaluate-division/

// You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i]
// represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.
// You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.
// Return the answers to all queries. If a single answer cannot be determined, return -1.0.
// Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

// Example 1:
// Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
// Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
// Explanation: 
// Given: a / b = 2.0, b / c = 3.0
// queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
// return: [6.0, 0.5, -1.0, 1.0, -1.0 ]

// Approach: DIY, then see you can understand the problem as a DFS/BFS in a graph.
	// note: remember when building the graph to add edges a->b and b->a as well.
// remember edge cases: one of the elements of the query not present in the graph, and division by itself.
double dfs(unordered_map<string, unordered_map<string, double>>& graph, string source, string target, unordered_set<string>& visited, double acc) {
	visited.insert(source);
	
	if (graph[source].find(target) != graph[source].end()) {
		acc *= graph[source][target];
		return acc;
	}
	
	for (const pair<string, double>& edge : graph[source]) {
		if (visited.find(edge.first) == visited.end()) {
			double acc_neigh = dfs(graph, edge.first, target, visited, acc * edge.second);
			if (acc_neigh != -1) {
				return acc_neigh;
			}
		}
	}

	return -1;
}

vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
	vector<double> results;

	// Build the graph.
	unordered_map<string, unordered_map<string, double>> graph;
	for (int i = 0; i < equations.size(); ++i) {
		vector<string> eq = equations[i];
		graph[eq[0]].insert({eq[1], values[i]});
		graph[eq[1]].insert({eq[0], 1.0/values[i]});
	}

	// For each query, do a DFS.
	for (const vector<string>& q : queries) {
		if (graph.find(q[0]) == graph.end() || graph.find(q[1]) == graph.end()) {
			results.push_back(-1);
			continue;
		}

		if (q[0] == q[1]) {
			results.push_back(1);
			continue;
		}

		unordered_set<string> visited = {};
		double acc = dfs(graph, q[0], q[1], visited, 1);

		results.push_back(acc);
	}

	return results;
}

int main() {
	vector<vector<string>> equations = {{"a","b"},{"b","c"}};
	vector<double> values = {2.0,3.0};
	vector<vector<string>> queries = {{"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}};

	cout << "Answer:" << endl;
	printVector(calcEquation(equations, values, queries));

	return 0;
}