#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/detonate-the-maximum-bombs (asked at Google)
// https://neetcode.io/solutions/detonate-the-maximum-bombs 
// Remember: look carefully at the examples of the problem description, it is a directed graph here, not
// an undirected graph (so Union-Find would not work), -> does not imply <- here, and the comparison is "<=" and
// not just "<" when comparing the radius with the distance.
// Remember: instead of using double and sqrt, it is safer to use long long to avoid approximation errors (since also using = in <=).
// Remember: doing bombs[i][2] * bombs[i][2] would give int overflow below, needs to cast to long long before that.
// Note: it is not if the circles intersect, but if bomb_j is inside the circle with center on bomb_i and 
// radius r_i (directed edge i -> j) or bomb_i is inside the circle with center on bomb_j and radius r_j (directed edge j -> i).

// You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt. This 
// area is in the shape of a circle with the center as the location of the bomb.
// The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi and yi 
// denote the X-coordinate and Y-coordinate of the location of the ith bomb, whereas ri denotes the radius of its range.

// You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that lie in its range. 
// These bombs will further detonate the bombs that lie in their ranges.
// Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed to detonate only one bomb.

int sizeOfComponentDfs(int i, const vector<vector<int>>& g, vector<bool>& visited) {
    visited[i] = true;
    int size = 1;
    for (int neighbor : g[i]) {
        if (!visited[neighbor]) {
            size += sizeOfComponentDfs(neighbor, g, visited);
        }
    }

    return size;
}

int maximumDetonation(vector<vector<int>>& bombs) {
    int n = bombs.size();
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long dx = bombs[i][0] - bombs[j][0];
            long long dy = bombs[i][1] - bombs[j][1];
            long long r_i = bombs[i][2];  // if had done just bombs[i][2] * bombs[i][2] below would have int overflow for radius 10^5 on leetcode (thus need to cast to long long already here, otherwise product of ints tries to save in an int format).
            long long r_j = bombs[j][2];
            long long squared_dist = dx * dx + dy * dy;
            if (squared_dist <= r_i * r_i) {  // attention, directed graph, -> does not imply <-, and <= here (not just <).
                g[i].push_back(j);
            }
            if (squared_dist <= r_j * r_j) {
                g[j].push_back(i);
            }
        }
    }

    int max_size = 0;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        visited.assign(n, false);  // better for leetcode time to not construct "visited" each time, just assign.
        max_size = max(max_size, sizeOfComponentDfs(i, g, visited));
    }

    return max_size;
}

int main() {
	cout << "Hello, World!";
	return 0;
}