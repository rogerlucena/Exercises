#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

// https://www.pramp.com/challenge/MW75pP53wAtzNPVLPG0d
// 	(Similar to https://www.interviewbit.com/problems/word-ladder-i/)
// 	Think in graphs here!
// 	Use Djikstra only if weighted edges (and no negative edges! remember Djikstra: http://www.inf.ufsc.br/grafos/temas/custo-minimo/dijkstra.html)
// 	Otherwise, a simple BFS will do the work :)
//	 remember here: understand first well the problem, ask questions e nao se afobar!!
//   target must be in "words", but not "source" (see example 2), Attention!!
//   complexity: do not forget to consider the complexity "k" of "isOneStepAway"!

// Shortest Word Edit Path
// Given two words source and target, and a list of words words, find the length of the
// shortest series of edits that transforms source to target.

// Each edit must change exactly one letter at a time, and each intermediate word
// (and the final target word) must exist in words.

// If the task is impossible, return -1.

// Examples:

// source = "bit", target = "dog"
// words = ["but", "put", "big", "pot", "pog", "dog", "lot"]
// output: 5
// explanation: bit -> but -> put -> pot -> pog -> dog has 5 transitions.

// source = "no", target = "go"
// words = ["to"]
// output: -1

bool isOneStepAway(const string &s1, const string &s2)
{
	if (s1.size() != s2.size())
	{
		return false;
	}

	int diff = 0;
	for (int i = 0; i < s1.size(); ++i)
	{
		if (s1[i] != s2[i])
		{
			++diff;
		}

		if (diff > 1)
		{
			return false;
		}
	}

	return diff == 1;
}

// O(N^2 * k) time (build the graph, k is the max size of a word, remember it!)
// and space O(N^2) worst case (fully connected)
int shortestWordEditPath(const string &source,
						 const string &target,
						 const vector<string> &words)
{
	unordered_map<string, unordered_set<string>> g;

	vector<string> nodes(words);
	nodes.push_back(source);

	for (int i = 0; i < nodes.size(); ++i)
	{
		string from = nodes[i];
		for (int j = i + 1; j < nodes.size(); ++j)
		{
			string to = nodes[j];
			if (isOneStepAway(from, to))
			{
				g[from].insert(to);
				g[to].insert(from);
			}
		}
	}

	queue<pair<string, int>> q;
	q.push({source, 0});
	unordered_set<string> enqueued;
	enqueued.insert(source);

	while (!q.empty())
	{
		pair<string, int> p = q.front();
		q.pop();
		int d = p.second;
		string n = p.first;

		if (n == target)
		{
			return d;
		}

		for (string neigh : g[n])
		{
			if (enqueued.find(neigh) == enqueued.end())
			{
				q.push({neigh, d + 1});
				enqueued.insert(neigh);
			}
		}
	}

	return -1;
}

int main()
{
	string A = "bit";
	string B = "dog";
	vector<string> C = {"but", "put", "big", "pot", "pog", "dog", "lot"}; // ans: 5

	cout << "Answer: " << shortestWordEditPath(A, B, C) << endl;

	return 0;
}