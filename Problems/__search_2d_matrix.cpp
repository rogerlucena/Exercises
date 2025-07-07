#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/search-a-2d-matrix
// https://neetcode.io/problems/search-2d-matrix
// Quick review: nice to use "/ COLS" and "% COLS" to work with indexes in 2D-matrix - remember this.

// You are given an m x n integer matrix matrix with the following two properties:

// Each row is sorted in non-decreasing order.
// The first integer of each row is greater than the last integer of the previous row.
// Given an integer target, return true if target is in matrix or false otherwise.

// You must write a solution in O(log(m * n)) time complexity.

// Ex 1:
// Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
// Output: true

// Constraints:
// m == matrix.length
// n == matrix[i].length
// 1 <= m, n <= 100
// -104 <= matrix[i][j], target <= 104


// Only one pass, Neetcode solution, nice to use "/ COLS" and "% COLS" to work with indexes in 2D-matrix - remember this.
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int ROWS = matrix.size(), COLS = matrix[0].size();

    int l = 0, r = ROWS * COLS - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        int row = m / COLS, col = m % COLS; // well done.
        if (target > matrix[row][col]) {
            l = m + 1;
        } else if (target < matrix[row][col]) {
            r = m - 1;
        } else {
            return true;
        }
    }
	
    return false;
}

// My solution more complex below:
bool searchMatrix(vector<vector<int>>& matrix, int target) {
	int m = matrix.size(), n = matrix[0].size();
	
	int left = 0, right = m - 1;
	while (left < right) {
        int mid = left + (right - left) / 2;
		if (matrix[mid][0] > target) {
			right = mid - 1;
		} else if (matrix[mid+1][0] <= target) {
			left = mid + 1;
		} else {
			left = mid;
			right = mid;
		}
    }

	int row = left;
	left = 0;
	right = n - 1;
	while (left <= right) {
        int mid = left + (right - left) / 2;
		if (matrix[row][mid] == target) {
			return true;
		}

		if (matrix[row][mid] < target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
    }

	return false;
}

int main() {
	cout << "Hello, World!";
	return 0;
}