#include <iostream>
#include <vector>
#include <unordered_map>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/word-search-ii/

// Given an m x n board of characters and a list of strings words, return all words on the board.

// Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally
// or vertically neighboring. The same letter cell may not be used more than once in a word.

// O(N * (4*3^{L-1})) in time, where N is the total number of cells in board and L is the size of the largest word seached.
// (maybe can improve performance verifying char match before recursion, and making "word" and "children" public / not using
// unnecessary methods to access private info)
class TrieNode {
	unordered_map<char, TrieNode*> children;
	string word;

public:
	TrieNode() {
		children = {};
		word = "";
	}
	
	void insert(const string &word) {
		TrieNode* currNode = this;
		for (int i = 0; i < word.size(); ++i) {
			if (currNode->children.find(word[i]) == currNode->children.end()) {
				currNode->children[word[i]] = new TrieNode();
			}
			currNode = currNode->children[word[i]];
		}

		currNode->word = word;
	}

	TrieNode* getChild(char c) {
		return this->children[c];
	}

	string getWord() {
		return this->word;
	}

	void clearWord() {
		this->word = "";
	}

	bool hasChildren() {
		return !this->children.empty();
	}

	void removeChild(char c) {
		this->children.erase(c);
	}
};

void tryFrom(int row, int col, vector<vector<char>>& board, TrieNode* root, vector<string>& found) {
	char currChar = board[row][col];
	TrieNode* child = root->getChild(currChar);
	if (child == nullptr) {
		return;
	}
	if (!child->getWord().empty()) {
		found.push_back(child->getWord());
		child->clearWord(); // to avoid repeated words in "found".
	}
	
	board[row][col] = '#';
	vector<int> rowOffsets = {1, -1, 0, 0};
	vector<int> colOffsets = {0, 0, 1, -1};
	for (int d = 0; d < 4; ++d) {
		int nRow = row + rowOffsets[d];
		int nCol = col + colOffsets[d];
		if (nRow < 0 || nRow >= board.size() || nCol < 0 || nCol >= board[0].size() || board[nRow][nCol] == '#') {
			continue;
		}
		tryFrom(nRow, nCol, board, child, found);
	}

	board[row][col] = currChar;

	// Optimization: gradatively remove empty leaves.
	if (!child->hasChildren()) {
		root->removeChild(currChar);
	}

	return;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
	TrieNode* root = new TrieNode();
	for (string w : words) {
		root->insert(w);
	}

	vector<string> found = {};

	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[0].size(); ++j) {
			tryFrom(i, j, board, root, found);
		}
	}

	return found;
}


int main() {
	vector<vector<char>> board1 = {{'o','a','a','n'},
								 {'e','t','a','e'},
								 {'i','h','k','r'},
								 {'i','f','l','v'}}; // ans: ["eat","oath"]
	vector<string> words1 = {"oath","pea","eat","rain"};

	vector<vector<char>> board = {{'o','a','b','n'},
								 {'o','t','a','e'},
								 {'a','h','k','r'},
								 {'a','f','l','v'}}; // ans: ["oa","oaa"]
	vector<string> words = {"oa","oaa"};

	vector<string> ans = findWords(board, words);
	printVector(ans);
	return 0;
}