#include <iostream>
#include <vector>
#include <set>

using namespace std;

/*
  For a position with zero in the matrix, set the entire row and column to zero.

  https://leetcode.com/explore/interview/card/top-interview-questions-medium/103/array-and-strings/777/
*/

class Solution {
 public:
  void setZeroes(vector<vector<int>>& matrix) {
    set<int> columnsToZero;
    set<int> rowsToZero;
    for (int i = 0; i < matrix.size(); ++i) {
      for (int j = 0; j < matrix[0].size(); ++j) {
        if(matrix[i][j] == 0){
          rowsToZero.insert(i);
          columnsToZero.insert(j);
        }
      }
    }

    for (int i : rowsToZero) {
      for (int j = 0; j < matrix[0].size(); ++j) {
        matrix[i][j] = 0;
      }
    }

    for (int j : columnsToZero) {
      for (int i = 0; i < matrix.size(); ++i) {
        matrix[i][j] = 0;
      }
    }

  }
};

int main() {
  vector<vector<int>> matrix = {{1, 2, 0}, {3, 3, 3}, {0, 12, 1}};

  Solution sol;
  sol.setZeroes(matrix);

  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[0].size(); ++j) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}