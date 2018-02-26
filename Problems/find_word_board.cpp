#include <iostream>
#include <vector>

using namespace std;

/*
  Find if the asked word appears on the board.

  https://leetcode.com/explore/interview/card/top-interview-questions-medium/109/backtracking/797/
*/

class Solution {
 public:

  bool existFrom(vector<vector<char>>& board, string word, int i, int j, vector<vector<bool>> visited) {
    if (board[i][j] != word[0]) return false;
    if(word.size() == 1) return true;
    int L = board.size();
    int C = board[0].size();
    bool b = false;
    visited[i][j] = true;

    if (i+1 < L && !visited[i+1][j]) b = b || existFrom(board, word.substr(1, word.size()-1), i+1, j, visited);
    if (i-1 >= 0 && !visited[i-1][j]) b = b || existFrom(board, word.substr(1, word.size()-1), i-1, j, visited);
    if (j+1 < C && !visited[i][j+1]) b = b || existFrom(board, word.substr(1, word.size()-1), i, j+1, visited);
    if (j-1 >= 0 && !visited[i][j-1]) b = b || existFrom(board, word.substr(1, word.size()-1), i, j-1, visited);

    return b;
  }

  bool exist(vector<vector<char>>& board, string word) {
    char c = word[0];
    int L = board.size();
    int C = board[0].size();

    for (int i = 0; i < L; ++i) {
      for (int j = 0; j < C; ++j) {
        if(board[i][j] != word[0]) continue;
        vector<vector<bool>> visited(L, vector<bool>(C, 0));
        bool b = existFrom(board, word, i, j, visited);
        if (b) return true;
      }
    }
    return false;
  }
};

int main()
{
  string word = "ABCCED";
  vector<vector<char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};

  Solution sol;
  cout << sol.exist(board, word) << endl;

  return 0;
}