#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://www.interviewbit.com/problems/clone-graph/
// DFS over original and hash map saving original -> clone

// Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.

// Definition for undirected graph.
struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode*> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};

UndirectedGraphNode* cloneGraphHelper(const UndirectedGraphNode* node, unordered_map<const UndirectedGraphNode*, UndirectedGraphNode*> &orginalAndClone) {
	if(!node) {
		return nullptr;
	}

	UndirectedGraphNode* newNode = new UndirectedGraphNode(node->label);
	orginalAndClone[node] = newNode;

	for(UndirectedGraphNode* neigh : node->neighbors) {
		if(orginalAndClone.find(neigh) == orginalAndClone.end()) {
			newNode->neighbors.push_back(cloneGraphHelper(neigh, orginalAndClone));
		} else {
			newNode->neighbors.push_back(orginalAndClone[neigh]);
		}
	}

	return orginalAndClone[node];
}

UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node) {
	unordered_map<const UndirectedGraphNode*, UndirectedGraphNode*> orginalAndClone;
	return cloneGraphHelper(node, orginalAndClone);
}

int main() {
	cout << "Hello, World!";
	return 0;
}