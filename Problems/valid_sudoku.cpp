#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// https://www.interviewbit.com/problems/valid-sudoku/

// Determine if a Sudoku is valid, according to: http://sudoku.com.au/TheRules.aspx
// The Sudoku board could be partially filled, where empty cells are filled with the character ‘.’.

int isValidSudoku(const vector<string> &A) {
	if(A.empty()) {
		return 1;
	}
	int nLines = A.size();
	int nColumns = A[0].size();
	int nSquares = (nLines/3) * (nColumns/3);

	vector<unordered_set<char>> lines (nLines);
	vector<unordered_set<char>> columns (nColumns);
	vector<unordered_set<char>> squares (nSquares);

	for(int i = 0; i < nLines; ++i) {
		for(int j = 0; j < nColumns; ++j) {
			char v = A[i][j];
			if(v != '.') {
				bool foundInLine = lines[i].find(v) != lines[i].end() ;
				bool foundInColumn = columns[j].find(v) != lines[j].end();
				bool foundInSquare = squares[(i/3)*3 + j/3].find(v) != squares[(i/3)*3 + j/3].end();
				if(foundInLine || foundInColumn || foundInSquare) {
					return 0;
				} else {
					lines[i].insert(v);
					columns[j].insert(v);
					squares[(i/3)*3 + j/3].insert(v);
				}
			}
		}
	}

	return 1; 
}

int main() {
	vector<string> A = {"53..7....", "6..195...", ".98....6.", "8...6...3", "4..8.3..1", "7...2...6", ".6....28.", "...419..5", "....8..79"};
	cout << "Answer: " << isValidSudoku(A) << endl;

	return 0;
}