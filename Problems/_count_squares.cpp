#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://neetcode.io/problems/count-squares
// https://leetcode.com/problems/detect-squares
// Remember: geometry, think of the diagonal of the square defining the square (see "count()" below), and 
// only "de pé" squares allowed here it seems.

// You are given a stream of points consisting of x-y coordinates on a 2-D plane. Points can be added and queried
// as follows:

// Add - new points can be added to the stream into a data structure. Duplicate points are allowed and should be 
// treated as separate points.
// Query - Given a single query point, count the number of ways to choose three additional points from the data
// structure such that the three points and the query point form a square. The square must have all sides parallel 
// to the x-axis and y-axis, i.e. no diagonal squares are allowed. Recall that a square must have four equal sides.
// Implement the CountSquares class:

// CountSquares() Initializes the object.
// void add(int[] point) Adds a new point point = [x, y].
// int count(int[] point) Counts the number of ways to form valid squares with point point = [x, y] as described above.

class CountSquares {
    vector<vector<int>> points;
    unordered_map<string, int> points_count;

    string getKey(const vector<int>& point) {  // could have used long as key, doing long key = (static_cast<long>(x) << 32) | static_cast<long>(y); (but still possibility of conflict - rare)
        string key = to_string(point[0]);
        key += ",";
        key += to_string(point[1]);

        return key;
    }
public:
    CountSquares() {
        // points = {};  // not needed as their default constructor already does this, only if you want to emphasize clarity for human readers.
        // points_count = {};
    }
    
    void add(vector<int> point) {
        points.push_back(point);
        string key = getKey(point);
        // if (!points_count.count(key)) {
        //     points_count[key] = 0;
        // }
        ++points_count[key];
    }

    // For the queried {qx, qy}, test if each {x, y} can define a diagonal of a square (4 possibilities 
    // given {qx, qy}). To get the desired coordinates of the other 2 points think of {qx, qy} at the
    // top-right of the square (for the other 3 cases the coordinates below are also correct):
    int count(vector<int> point) {
        int qx = point[0];  // queried x.
        int qy = point[1];  // queried y.
        int n_squares = 0;
        for (const vector<int>& p : points) {  // if we have repeated points, they will already be correctly counted twice here.
            int x = p[0];
            int y = p[1];
            if (abs(qx - x) != abs(qy - y) || x == qx || y == qy) {
                continue;
            }
            n_squares += points_count[getKey({qx, y})] * points_count[getKey({x, qy})];
        }

        return n_squares;
    }
};

int main() {
	cout << "Hello, World!";
	return 0;
}