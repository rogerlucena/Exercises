#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/cheapest-flight-path
// https://leetcode.com/problems/cheapest-flights-within-k-stops
// Remember: Shortest path in weighted graph - Bellman-Ford allows to directly use "k" stops 
// here ("at most k + 1 edges" restriction), which Dijkstra wouldn't directly.

// There are n airports, labeled from 0 to n - 1, which are connected by some flights. You are given an array
// flights where flights[i] = [from_i, to_i, price_i] represents a one-way flight from airport from_i to airport
// to_i with cost price_i. You may assume there are no duplicate flights and no flights from an airport to itself.

// You are also given three integers src, dst, and k where:

// src is the starting airport
// dst is the destination airport
// src != dst
// k is the maximum number of stops you can make (not including src and dst)
// Return the cheapest price from src to dst with at most k stops, or return -1 if it is impossible.

// Example:
// Input: n = 4, flights = [[0,1,200],[1,2,100],[1,3,300],[2,3,100]], src = 0, dst = 3, k = 1
// Output: 500
// Explanation:
// The optimal path with at most 1 stop from airport 0 to 3 is shown in red, with total cost 200 + 300 = 500.
// Note that the path [0 -> 1 -> 2 -> 3] costs only 400, and thus is cheaper, but it requires 2 stops, which is more than k.

// Constraints:
// 1 <= n <= 100
// fromi != toi
// 1 <= pricei <= 1000
// 0 <= src, dst, k < n

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    for (int i = 1; i <= k + 1; ++i) {  // #edges in the longest shortest path allowed here ("k" stops). 
        vector<int> tmp_dist = dist;  // do not forget this! error on submission for example above otherwise.
        for (const vector<int>& flight : flights) {
            int from = flight[0];
            int to = flight[1];
            int price = flight[2];
            if (dist[from] < INT_MAX && dist[from] + price < tmp_dist[to]) {
                tmp_dist[to] = dist[from] + price;
                // update predecessor[to] here if asked for path as well.
            }
        }
        dist = tmp_dist;
    }

    return dist[dst] < INT_MAX ? dist[dst] : -1;
}

int main() {
	cout << "Hello, World!";
	return 0;
}