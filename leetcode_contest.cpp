#include <iostream>
#include <vector>
#include <unordered_map>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/contest/biweekly-contest-12

void printGraph(unordered_map<int, vector<int>> &g) {
	for(pair<int, vector<int>> p : g) {
		cout << "Node: " << p.first << endl;
		printVector(p.second);
	}
}

int dfs(int n, unordered_map<int, const vector<int>> &g, int parent) {
	int maxPathToLeaf = 0;
	for(int neigh: g[n]) {
		if(neigh != parent) {
			int maxCandidate = 1 + dfs(neigh, g, n);
			maxPathToLeaf = maxCandidate > maxPathToLeaf ? maxCandidate : maxPathToLeaf;
		}
	}

	return maxPathToLeaf;
}

int diameterFromRoot(int n, unordered_map<int, const vector<int>> &g) {
	int maxPathToLeaf = 0;
	int secondMaxPathToLeaf = 0;
	for(int neigh : g[n]) {
		int maxCandidate = 1 + dfs(neigh, g, n);
		if(maxCandidate >= maxPathToLeaf) {
			secondMaxPathToLeaf = maxPathToLeaf;
			maxPathToLeaf = maxCandidate;
		} else {
			secondMaxPathToLeaf = maxCandidate > secondMaxPathToLeaf ? maxCandidate : secondMaxPathToLeaf;
		}
	}
}

int treeDiameter(vector<vector<int>> &edges) {
	unordered_map<int, vector<int>> g;
	for(vector<int> e : edges) {
		g[e[0]].push_back(e[1]);
		g[e[1]].push_back(e[0]);
	}

	// printGraph(g);

	int best = 0;


	return best;
}

int main() {
	vector<vector<int>> edges = {{0,1},{0,2}};
	// vector<vector<int>> {{0,1},{0,2],{2,3],{2,4],{2,5],{4,6],{0,7],{0,8],[3,9],[8,10],[8,11],[2,12],[7,13],[4,14],[12,15],[13,16],[14,17],[11,18],[18,19],[16,20],[2,21],[4,22],[9,23],[1,24],[4,25],[15,26],[19,27],[2,28],[16,29],[9,30],[21,31],[13,32],[5,33],[9,34],[2,35],[17,36],[1,37],[33,38],[0,39],[18,40],[29,41],[1,42],[37,43],[13,44],[19,45],[3,46],[1,47],[18,48]}; // expected: 10
	
	cout << "Answer: " << treeDiameter(edges) << endl;
	return 0;
}




// vector<int> transformArray(vector<int>& arr) {
// 	bool change = true;
// 	while(change) {
// 		change = false;
// 		vector<int> prevArr(arr);
// 		for(int i = 1; i < arr.size() - 1; ++i) {
// 			if(arr[i] > prevArr[i-1] && arr[i] > prevArr[i+1]) {
// 				--arr[i];
// 				change = true;
// 			} else if(arr[i] < prevArr[i-1] && arr[i] < prevArr[i+1]) {
// 				++arr[i];
// 				change = true;
// 			}
// 		}
// 	}

// 	return arr;
// }

// int main() {
// 	vector<int> arr = {2,1,2,1,1,2,2,1}; // expected: [2,2,1,1,1,2,2,1]
// 	cout << "Answer:" << endl;
// 	printVector(transformArray(arr));

// 	return 0;
// }