#include <iostream>
#include <vector>

#include <unordered_set>

using namespace std;

// https://www.interviewbit.com/problems/travelling-saleman-problem/


// Best complexity (with DP): O(n^2 . 2^n)
// https://www.geeksforgeeks.org/travelling-salesman-problem-set-1/
// More on complexity: https://cs.stackexchange.com/questions/90149/analysis-of-time-complexity-of-travelling-salesman-problem

// Given a matrix B of size A x A where B[i][j] denotes the cost of moving from city i to city j.

// Your task is to complete a tour from the city 0 (0 based index) to all other cities such that you 
// visit each city at-most once and then at the end come back to city 0 in min cost.

// Return the minimum cost of the tour.
// (website solution -> it seems that you cannot use B[i][j] if it is zero neither)

// Constraints:
// 1 <= A <= 10
// 0 <= B[i][j] <= 10000
// B[i][i] = 0
// For Example:

// Input 1:
//     A = 3 , B = [[0 500 100] [100 0 500] [500 100 0]]
// Output 1:
//     300
// Explanation 1:
//     The Tour is 0 -> 2 -> 1 -> 0

// Input 2:
//     A = 2 , B = [[0 5] [7 0]]
// Output 2:
//     12

// Website solution:
void tsp(vector<vector<int>> arr, int n, int cost, int &mncost, int count, vector<bool> &vis, int pos) {
    if(count == n) {
        cost += arr[pos][0];
        if (cost < mncost) {
        	mncost = cost;
		}
        return;
    }
    
    for(int i = 1; i < n; ++i) {
        if(arr[pos][i] > 0 && !vis[i]) {
            vis[i] = true;
            tsp(arr, n, cost + arr[pos][i], mncost, count + 1, vis, i);
            vis[i] = false;
        }
    }
}

int solve(int A, vector<vector<int>> &B) {
    vector<bool> vis(A, false);
    vis[0] = true;

    int cost = 0, mncost = INT_MAX;
    int count = 1, pos = 0;
    tsp(B, A, 0, mncost, count, vis, pos);

    return mncost;
}


// My solution:
// if using INT_MAX we have int overlow, verify why later
int solveHelper(int city, int time, vector<vector<int>> &B, unordered_set<int> &visited) {
	int ans = 1000000;
	if(time == B.size()-1) {
		ans = B[city][0];
	} else {
		for(int neigh = 1; neigh < B.size(); ++neigh) {
			if(visited.find(neigh) == visited.end() && B[city][neigh] > 0) {
				visited.insert(neigh);
				ans = min(ans, B[city][neigh] + solveHelper(neigh, time+1, B, visited));
				visited.erase(neigh);
			}
		}
	}

	return ans;
}

int mySolve(int A, vector<vector<int>> &B) {
	// vector<vector<int>> memo(A, vector<int>(A, INT_MAX));
	unordered_set<int> visited;

	return solveHelper(0, 0, B, visited);
}


int main() {
	// int A = 3; // ans: 300
	// vector<vector<int>> B = {{0, 500, 100}, {100, 0, 500}, {500, 100, 0}};

	// int A = 2; // ans: 12
	// vector<vector<int>> B = {{0, 5}, {7, 0}};

	int A = 4; // ans: 17
	vector<vector<int>> B = {
		{0, 1, 2, 3},
		{3, 0, 2, 1},
		{5, 6, 0, 7},
		{8, 9, 0, 0}
	}; // 0 -> 1 -> 3 -> 2 -> 0
	   // 1 1 0 5

	cout << "Answer: " << solve(A, B) << endl;

	return 0;
}