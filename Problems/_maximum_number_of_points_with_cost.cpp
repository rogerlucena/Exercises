#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/maximum-number-of-points-with-cost (Google, solution in "solutions" section)
// Remember: Bottom-up DP, optimized from O(N^2 * M) (time limit exceeds) to O(N * M) with "left_max" and "right_max" below.

// You are given an m x n integer matrix points (0-indexed). Starting with 0 points, you want to maximize the number of points 
// you can get from the matrix.

// To gain points, you must pick one cell in each row. Picking the cell at coordinates (r, c) will add points[r][c] to your score.

// However, you will lose points if you pick a cell too far from the cell that you picked in the previous row. For every two 
// adjacent rows r and r + 1 (where 0 <= r < m - 1), picking cells at coordinates (r, c1) and (r + 1, c2) will subtract abs(c1 - c2) from your score.

// Return the maximum number of points you can achieve.

// Constraints:
// m == points.length
// n == points[r].length
// 1 <= m, n <= 10^5
// 1 <= m * n <= 10^5
// 0 <= points[r][c] <= 10^5

long long maxPoints(vector<vector<int>>& points) {
    const int ROWS = points.size();
    const int COLS = points[0].size();
    vector<vector<long long>> memo(ROWS, vector<long long>(COLS, 0));
    for (int j = 0; j < COLS; ++j) {
        memo[ROWS-1][j] = points[ROWS-1][j];  // could use static_cast<long long>, but for the sake of speed.
    }

    vector<long long> left_max(COLS);
    vector<long long> right_max(COLS);
    for (int i = ROWS - 2; i >= 0; --i) {
        left_max[0] = memo[i + 1][0];
        for (int j = 1; j < COLS; ++j) {
            left_max[j] = max(left_max[j - 1] - 1, memo[i + 1][j]);
        }
        right_max[COLS - 1] = memo[i + 1][COLS - 1];
        for (int j = COLS - 2; j >= 0; --j) {
            right_max[j] = max(right_max[j + 1] - 1, memo[i + 1][j]);
        }
        
        for (int j = 0; j < COLS; ++j) {
            memo[i][j] = max(left_max[j], right_max[j]) + points[i][j];
        }
    }

    return *max_element(memo[0].begin(), memo[0].end());
}
// Could even optimize the space complexity above since we only need previous_row and current_row -> O(N) in space, instead of O(N * M) in space with memo above.

int main() {
	cout << "Hello, World!";
	return 0;
}