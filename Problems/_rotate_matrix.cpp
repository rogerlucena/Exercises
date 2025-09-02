#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/rotate-matrix
// https://leetcode.com/problems/rotate-image
// Remember: easier way is to reverse vertically and then transpose.

// Given a square n x n matrix of integers matrix, rotate it by 90 degrees clockwise.
// You must rotate the matrix in-place. Do not allocate another 2D matrix and do the rotation.

// Example:
// Input: matrix = [
//   [1,2,3],
//   [4,5,6],
//   [7,8,9]
// ]
// Output: [
//   [7,4,1],
//   [8,5,2],
//   [9,6,3]
// ]

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    // Reverse the matrix vertically.
    for (int i = 0; i < n / 2; ++i) { // could have done reverse(matrix.begin(), matrix.end()) as well.
        for (int j = 0; j < n; ++j) {
            swap(matrix[i][j], matrix[n - 1 - i][j]);
        }
    }

    // Transpose the matrix.
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

// Or rotate by four cells (easier to make mistakes).
void rotate(vector<vector<int>>& matrix) {
    int l = 0;
    int r = matrix.size() - 1;

    while (l < r) {
        for (int i = 0; i < r - l; i++) {
            int top = l;
            int bottom = r;

            // save the topleft
            int topLeft = matrix[top][l + i];

            // move bottom left into top left
            matrix[top][l + i] = matrix[bottom - i][l];

            // move bottom right into bottom left
            matrix[bottom - i][l] = matrix[bottom][r - i];

            // move top right into bottom right
            matrix[bottom][r - i] = matrix[top + i][r];

            // move top left into top right
            matrix[top + i][r] = topLeft;
        }
        r--;
        l++;
    }
}

int main() {
	cout << "Hello, World!";
	return 0;
}