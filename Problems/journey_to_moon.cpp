#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*

-- Problem Starement: https://www.hackerrank.com/challenges/journey-to-the-moon/problem

 Basically astronauts from different countries, an edge represents same nationality,
find the number of possible pairs of astronauts (each from a different country)

Input 0:
5 3
0 1
2 3
0 4

Output 0:
6

Input 1:
4 1
0 2

Output 1:
5

// My solution still has to be debbuged for bigger cases.

*/

int getNumberOfElementDFS(vector<vector<int>> &graph, int pos, vector<bool> &visited) {
    //cout << pos << endl;
    int nElements = 1; // at least the current astronaut (element) in that country (connected component)
    visited[pos] = true;
    for(int i=0; i<graph[pos].size(); ++i) {
        if(visited[graph[pos][i]]) continue;
        nElements += getNumberOfElementDFS(graph, graph[pos][i], visited);
    }
    return nElements;
}

// connectedComponents.size() will be the number of connected components (countries)
// and every position has the number of astronauts from that country
vector<int> getConnectedComponentsAndSizes(int N, vector<vector<int>> &graph) {
    vector<int> connectedComponents;
    vector<bool> visited(N, false);
    for(int i=0; i<N; ++i) {
        if(visited[i])
            continue;
        int nElements = getNumberOfElementDFS(graph, i, visited);
        connectedComponents.push_back(nElements);
    }

    return connectedComponents;
}

using namespace std;
int main()
{
    int N, P;
    cin >> N;
    cin >> P;

    vector<vector<int>> graph;
    graph.reserve(N); // N astronauts

    for(int i=1; i<=P; ++i) {
        int from, to;
        cin >> from;
        cin >> to;
        graph[from].push_back(to);
    }

    vector<int> connectedComponents = getConnectedComponentsAndSizes(N, graph);

    /*
    for(int i=0; i<connectedComponents.size(); ++i) {
        cout << "Component " << i << ": " << connectedComponents[i] << endl;
    }
    */

    int nPossibilities = 0;
    for(int i=0; i<connectedComponents.size(); ++i) {
        for(int j=i+1; j<connectedComponents.size(); ++j) {
            nPossibilities += connectedComponents[i]*connectedComponents[j];
        }
    }

    cout << nPossibilities << endl;

    return 0;
}