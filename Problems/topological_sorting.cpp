// A C++ program to print topological sorting of a DAG
#include<iostream>
#include <list>
#include <stack>
using namespace std;

// Very good implementation as well: https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/
// (this one above also verifies if the given graph is indeed a DAG)
// (I prefer this one above = first one below, other than the second one below)
// The first vertex in topological sorting is always a vertex with in-degree as 0 (a vertex with no in-coming edges).
// Obs: A DAG G has at least one vertex with in-degree 0 and one vertex with out-degree 0.

// 1)

// A C++ program to print topological 
// sorting of a graph using indegrees. 

// Algorithm: Steps involved in finding the topological ordering of a DAG:

// Step 1: Compute in-degree (number of incoming edges) for each of the vertex present in the DAG and 
// initialize the count of visited nodes as 0.

// Step 2: Pick all the vertices with in-degree as 0 and add them into a queue (Enqueue operation)

// Step 3: Remove a vertex from the queue (Dequeue operation) and then.

// Increment count of visited nodes by 1.
// Decrease in-degree by 1 for all its neighboring nodes.
// If in-degree of a neighboring nodes is reduced to zero, then add it to the queue.
// Step 5: Repeat Step 3 until the queue is empty.

// Step 6: If count of visited nodes is not equal to the number of nodes in the graph then the topological sort is not 
// possible for the given graph.


// Class to represent a graph 
class Graph { 
    // No. of vertices' 
    int V; 
  
    // Pointer to an array containing 
    // adjacency listsList 
    list<int>* adj; 
  
public: 
    // Constructor 
    Graph(int V); 
  
    // Function to add an edge to graph 
    void addEdge(int u, int v); 
  
    // prints a Topological Sort of 
    // the complete graph 
    void topologicalSort(); 
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int u, int v) 
{ 
    adj[u].push_back(v); 
} 
  
// The function to do 
// Topological Sort. 
void Graph::topologicalSort() 
{ 
    // Create a vector to store 
    // indegrees of all 
    // vertices. Initialize all 
    // indegrees as 0. 
    vector<int> in_degree(V, 0); 
  
    // Traverse adjacency lists 
    // to fill indegrees of 
    // vertices.  This step 
    // takes O(V+E) time 
    for (int u = 0; u < V; u++) { 
        list<int>::iterator itr; 
        for (itr = adj[u].begin(); 
             itr != adj[u].end(); itr++) 
            in_degree[*itr]++; 
    } 
  
    // Create an queue and enqueue 
    // all vertices with indegree 0 
    queue<int> q; 
    for (int i = 0; i < V; i++) 
        if (in_degree[i] == 0) 
            q.push(i); 
  
    // Initialize count of visited vertices 
    int cnt = 0; 
  
    // Create a vector to store 
    // result (A topological 
    // ordering of the vertices) 
    vector<int> top_order; 
  
    // One by one dequeue vertices 
    // from queue and enqueue 
    // adjacents if indegree of 
    // adjacent becomes 0 
    while (!q.empty()) { 
        // Extract front of queue 
        // (or perform dequeue) 
        // and add it to topological order 
        int u = q.front(); 
        q.pop(); 
        top_order.push_back(u); 
  
        // Iterate through all its 
        // neighbouring nodes 
        // of dequeued node u and 
        // decrease their in-degree 
        // by 1 
        list<int>::iterator itr; 
        for (itr = adj[u].begin(); 
             itr != adj[u].end(); itr++) 
  
            // If in-degree becomes zero, 
            // add it to queue 
            if (--in_degree[*itr] == 0) 
                q.push(*itr); 
  
        cnt++; 
    } 
  
    // Check if there was a cycle 
    if (cnt != V) { 
        cout << "There exists a cycle in the graph\n"; 
        return; 
    } 
  
    // Print topological order 
    for (int i = 0; i < top_order.size(); i++) 
        cout << top_order[i] << " "; 
    cout << endl; 
} 

// Complexity Analysis:
// Time Complexity: O(V+E).
// The outer for loop will be executed V number of times and the inner for loop will be executed E number of times.
// Auxillary Space: O(V).
// The queue needs to store all the vertices of the graph. So the space required is O(V)
  
// Driver program to test above functions 
int main() 
{ 
    // Create a graph given in the 
    // above diagram 
    Graph g(6); 
    g.addEdge(5, 2); 
    g.addEdge(5, 0); 
    g.addEdge(4, 0); 
    g.addEdge(4, 1); 
    g.addEdge(2, 3); 
    g.addEdge(3, 1); 
  
    cout << "Following is a Topological Sort of\n"; 
    g.topologicalSort();  // 4 5 2 0 3 1
  
    return 0; 
} 



// 2) The implementation below uses a stack and does not verify if the given graph is a DAG.

/*

 Topological sorting implementation for the
 question 4.7 of Cracking the COding Interview (6th Edition) - only a tool for the solution here

 -- It is a sorting in which, for every edge, the sender appears
    before the receiver (respecting the local order)

 Graph:
      5                  4
  (5->2) (5->0)  (0<-4)     (4->1)
 2              0          1
   (2->3)      (3->1)
        3
*/

// Class to represent a graph
class Graph
{
  int V;    // No. of vertices'

  // Pointer to an array containing adjacency listsList
  list<int> *adj;

  // A function used by topologicalSort
  void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
 public:
  Graph(int V);   // Constructor

  // function to add an edge to graph
  void addEdge(int v, int w);

  // prints a Topological Sort of the complete graph
  void topologicalSort();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[],
                                stack<int> &Stack)
{
    // Mark the current node as visited.
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);

    // Push current vertex to stack which stores result
    Stack.push(v);
}

// The function to do Topological Sort. It uses recursive
// topologicalSortUtil()
void Graph::topologicalSort()
{
    stack<int> Stack;

    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    // Print contents of stack
    while (Stack.empty() == false) // only valid topo sort if you already know it is a DAG, otherwise gives an invalid topo ordering
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

// Driver program to test above functions
int main2()
{
    // Create a graph given in the above diagram
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "Following is a Topological Sort of the given graph:" << endl;
    g.topologicalSort();

    return 0;
}

