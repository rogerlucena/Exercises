#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://interviews.school/trie
// https://leetcode.com/problems/implement-trie-prefix-tree
// https://neetcode.io/problems/implement-prefix-tree

// Interesting too, search for strings on which the dots '.' represent any
// chars (use auxiliar recursive dfs method with index j for word and going through children - solution below): 
// https://leetcode.com/problems/design-add-and-search-words-data-structure
// https://neetcode.io/problems/design-word-search-data-structure

// Review: remember to use pointers when managing tree-like structures (like Trie) and wanting to actually move
// through it and change it indeed and not a copy of it.

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

	~Trie() {
		// Clean up allocated memory.
		for (auto& [_, child_node] : children) {
			delete child_node;
		}
	}
};
// Or separate TrieNode from PrefixTree (two classes, the first one just to encapsulate isEnd and children, the second holds 'TrieNode* root' and the methods)
// as done in Neetcode in the link above, or below.

// Time & Space Complexity for above (from Neetcode):
// Time complexity: 
// O(n) for each function call.
// Space complexity: 
// O(t)
// Where n is the length of the string and 
// t is the total number of TrieNodes created in the Trie.


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


// For the other problem "design-add-and-search-words-data-structure" the solution is below:

// Difference for the search method explained in the problem statement:
// bool search(word) Returns true if there is any string in the data structure that matches word or 
// false otherwise. word may contain dots '.' where dots can be matched with any letter.
// Example in main2 below.

// Constraints:
// 1 <= word.length <= 20
// word in addWord consists of lowercase English letters.
// word in search consist of '.' or lowercase English letters.
// There will be at most 2 dots in word for search queries.
// At most 10,000 calls will be made to addWord and search.

class TrieNode {
public:
    vector<TrieNode*> children;
    bool word;

    TrieNode() : children(26, nullptr), word(false) {}
};

class WordDictionary {
public:
    TrieNode* root;

    WordDictionary() : root(new TrieNode()) {}

    void addWord(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (cur->children[c - 'a'] == nullptr) {
                cur->children[c - 'a'] = new TrieNode();
            }
            cur = cur->children[c - 'a'];
        }
        cur->word = true;
    }

    bool search(string word) {
        return dfs(word, 0, root);
    }

private:
    bool dfs(string word, int j, TrieNode* root) {
        TrieNode* cur = root;

        for (int i = j; i < word.size(); i++) {
            char c = word[i];
            if (c == '.') {
                for (TrieNode* child : cur->children) {
                    if (child != nullptr && dfs(word, i + 1, child)) {
                        return true;
                    }
                }
                return false;
            } else {
                if (cur->children[c - 'a'] == nullptr) {
                    return false;
                }
                cur = cur->children[c - 'a'];
            }
        }
        return cur->word;
    }
};
// I thought about recalling "search" with substr above as well, but index as above is cleaner/better.

// Time & Space Complexity (from Neetcode):
// Time complexity:
// O(n) for addWord(), O(n) for search().
// Space complexity: 
// O(t+n)
// Where n is the length of the string and t is the total number of TrieNodes created in the Trie.

int main2() {
	// Example:
	WordDictionary* wordDictionary = new WordDictionary();
	wordDictionary->addWord("day");
	wordDictionary->addWord("bay");
	wordDictionary->addWord("may");
	cout << wordDictionary->search("say") << endl; // return false
	cout << wordDictionary->search("day") << endl; // return true
	cout << wordDictionary->search(".ay") << endl; // return true
	cout << wordDictionary->search("b..") << endl; // return true

	return 0;
}


// Also interesting problem asked at Google in the past:
// www.interviewbit.com/problems/shortest-unique-prefix

// Find shortest unique prefix to represent each word in the list.

// Example:
// Input: [zebra, dog, duck, dove]
// Output: {z, dog, du, dov}

// Nice idea: add a count to each child, increment while inserting, and only return the prefix when count == 1.
class Trie {
private:
	unordered_map<char, pair<Trie*, int>> children;
	bool is_end;

public:
	Trie() {
		children = {};
		is_end = false;
	}

	void insert(const string& s) {
		Trie* curr = this;
		for (char c : s) {
			if (!curr->children.count(c)) {
				curr->children[c] = make_pair(new Trie(), 0);
			}
			++curr->children[c].second;
			curr = curr->children[c].first;
		}
		curr->is_end = true;
	}

	string getShortestUniquePrefix(const string& s) {
		Trie* curr = this;
		string prefix = "";
		for (char c : s) {
			prefix += c;
			if (curr->children[c].second == 1) {
				return prefix;
			}
			curr = curr->children[c].first;
		}

		return prefix;
	}

	~Trie() {
		// Clean up allocated memory.
		for (auto& [_, pair] : children) {
			delete pair.first;
		}
	}
};

vector<string> prefix(vector<string>& A) {
	Trie trie;
	for (const string& s : A) {
		trie.insert(s);
	}

	vector<string> prefixes = {};
	for (const string& s : A) {
		prefixes.push_back(trie.getShortestUniquePrefix(s));
	}

	return prefixes;
}

int main3() {
	vector<string> input = {"zebra", "dog", "duck", "dove"};
	vector<string> output = prefix(input); // expected: {z, dog, du, dov}

	for (string s : output) {
		cout << s << endl;
	}

	return 0;
}

// For C++17 recomended to use smart pointers for safer memory management as well:
// #include <memory> // for unique_ptr and std::make_unique
// unordered_map<char, pair<unique_ptr<Trie>, int>> children;
// (...)
// curr->children[c] = make_pair(make_unique<Trie>(), 0);
// (...)
// Trie* curr = this;
// (...)
// curr = curr->children[c].first.get(); // get raw normal pointer (Trie*) from unique_ptr