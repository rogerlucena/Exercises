#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://interviews.school/trie
// https://leetcode.com/problems/implement-trie-prefix-tree/

// Trie (PRONUNCIA certa é "TRY", lembre disso, se nao o cara nao vai saber o que vc ta falando, ou mencione "PREFIX TREE") is
// a tree data structure used to retrieve a key in a strings dataset.
// There are various applications of this very efficient data structure, such as autocomplete and spellchecker.

// O(N) to add or search a word (optimal). If a lot of words with common prefixes, Trie optmizes memory.
// The root always has isEnd as false, it just stores the first chars of all possible words (in children).
// When dealing with prefixes, think about Tries:
	// Are there any words in the trie that start with the prefix P?
	// How many words in the trie start with the prefix P?
	// What are all the words in the trie that start with the prefix P?

// Implement the Trie class:

// Trie() initializes the trie object.
// void insert(String word) inserts the string word to the trie.
// boolean search(String word) returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
// boolean startsWith(String prefix) returns true if there is a previously inserted string word that has the prefix prefix, 
// and false otherwise.

class Trie {
private:
	bool isEnd;
	unordered_map<char, Trie*> children;

public:
    /** Initialize your data structure here. */
    Trie() {
        isEnd = false;
		children = {};
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* currNode = this;
		for (char c : word) {
			if (currNode->children.find(c) == currNode->children.end()) {
				currNode->children[c] = new Trie();
			}
			currNode = currNode->children[c];
		}
		currNode->isEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* currNode = this;
		for (char c : word) {
			if (currNode->children.find(c) == currNode->children.end()) {
				return false;
			}
			currNode = currNode->children[c];
		}

		return currNode->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* currNode = this;
		for (char c : prefix) {
			if (currNode->children.find(c) == currNode->children.end()) {
				return false;
			}
			currNode = currNode->children[c];
		}

		return currNode->isEnd || !currNode->children.empty();
    }
};

int main() {
	Trie* t = new Trie();
	t->insert("apple");
	cout << t->search("apple") << endl; // true
	cout << t->search("app") << endl; // false
	cout << t->startsWith("app") << endl; // true
	t->insert("app");
	cout << t->search("app") << endl; // true
	return 0;
}