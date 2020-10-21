#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/reorganize-string/

// Given a string S, check if the letters can be rearranged so that two characters that are adjacent 
// to each other are not the same.
// If possible, output any possible result. If not possible, return the empty string.

// Example 1:
// Input: S = "aab"
// Output: "aba"
// Example 2:

// Example 2:
// Input: S = "aaab"
// Output: ""

// Note:
// S will consist of lowercase letters and have length in range [1, 500].


// If at some point the number of occurrences of some character is greater than (N + 1) / 2, the task is impossible (Dirichlet).
// Invariant through the operations below (taking "mostCommon").
// Idea by construction: "sort the string S, so all of the same kind of letter occur in continuous blocks. Then when writing in 
// the following interleaving pattern, like S[3], S[0], S[4], S[1], S[5], S[2], adjacent letters never touch (see 3 = (N+1)/2). 
// Greedy taking always "mostCommon" below is a subcase of this construction.

// Time Complexity: O(N log A)), where N is the length of S, and A is the size of the alphabet. 
// If A is fixed, this complexity is O(N).
// Space Complexity: O(A). If A is fixed, this complexity is O(1).
string reorganizeString(string S) {
	unordered_map<char, int> count;
	for(char c : S) {
		if(count.find(c) != count.end()) {
			++count[c];
		} else {
			count[c] = 1;
		}
	}

	auto cmp = [](const pair<char, int> &p1, const pair<char, int> &p2) {return p1.second < p2.second;};
	priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> mostCommon(count.begin(), count.end(), cmp);

	string ans = "";
	pair<char, int> prev{'a', 0};
	while(!mostCommon.empty()) {
		pair<char, int> curr = mostCommon.top();
		// cout << "curr: " << curr.first << ", " << curr.second << endl;
		mostCommon.pop();
		ans.push_back(curr.first);
		--curr.second;

		if(prev.second > 0) {
			mostCommon.push(prev);
		}
		prev = curr;
	}

	return S.size() == ans.size() ? ans : "";
}

int main() {
	cout << "ans: " << reorganizeString("aab") << endl;
	return 0;
}