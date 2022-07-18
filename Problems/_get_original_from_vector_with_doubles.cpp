#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Given a vector of int, you create a new vector with the initial elements and all its duplicates, and then shuffles that.
// eg: {1, 2, 4} -> {1, 2, 2, 4, 4, 8} -> {2, 8, 1, 2, 4, 4}
// Given this final vector, could you return me the original initial one?
// eg: {2, 8, 1, 2, 4, 4} -> {1, 2, 4}

// Idea: think about a graph, it will be a graph of linear branches like below, first pass
// just to get the possible beginning of each, and then iterate through and the duplicates updating the counts.
// eg:
// 1 -> 2 -> 4 -> 8
// 5 -> 10
// 3 -> 6 -> 12
vector<int> GetOriginalVector(const vector<int>& v) {
	unordered_map<int, int> counts;
	for (int el : v) {
		if (counts.find(el) == counts.end()) {
			counts[el] = 0;
		}
		++counts[el];
	}

	vector<int> halves_present;
	for (int el : v) {
		if (el % 2 == 1) {
			continue;
		}
		int half = el / 2;
		if (counts.find(half) != counts.end()) {
			halves_present.push_back(half);
		}
	}

	sort(halves_present.begin(), halves_present.end());
	vector<int> original;
	for (int half : halves_present) {
		int curr = half;
		while (counts.find(curr) != counts.end() && counts[curr] > 0) {
			original.push_back(curr);
			--counts[curr];
			int next = 2 * curr;
			--counts[next];
			curr = next;
		}
	}

	return original;
}

int main() {
	// vector<int> v = {2, 8, 1, 2, 4, 4}; // ans: {1, 2, 4}
	vector<int> v = {1, 5, 20, 2, 10, 40}; // ans: {1, 5, 20}
	for (int el : GetOriginalVector(v)) {
		cout << el << " ";
	}
	cout << endl;
	return 0;
}