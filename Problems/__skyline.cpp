#include <iostream>
#include <vector>
#include <set>

#include "tools.cpp"

using namespace std;

// https://leetcode.com/problems/the-skyline-problem/solution/

// Given the {leftPos, rightPos, height} of a number of buildings, return the key points
// of the resulting skyline (leftmost point of all horizontal lines).

// Solution link: https://zxi.mytechroad.com/blog/tree/leetcode-218-the-skyline-problem/

// Idea: create a vector of "Events" fron the input, sorte the events wrt the x coordinate,
// auxiliar data structure to O(1) access to maxHeight (multiset), attention to corner cases
	// if same x, if "entering": process highest first, if "leaving": process lowest first
class Solution {
	multiset<int> hs_;

	int getMaxHeight() {
		return hs_.empty() ? 0 : *hs_.rbegin();
	}

public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
		hs_.clear();

        typedef pair<int, int> Event; // x position and height (with positive height if "entering", and negative height if "leaving")
		vector<Event> events;
		for(vector<int> b : buildings) {
			events.emplace_back(b[0], b[2]);
			events.emplace_back(b[1], -b[2]);
		}

		// sort events by x:
		sort(events.begin(), events.end(), [](const Event& e1, const Event& e2) {
			if(e1.first == e2.first) {
				return e1.second > e2.second;
			}
			return e1.first < e2.first;
		});

		vector<vector<int>> ans;
		for(Event e : events) {
			int x = e.first;
			bool entering = e.second > 0;
			int h = abs(e.second);
			if(entering) {
				if(h > this->getMaxHeight()) {
					ans.push_back({x, h});
				}
				hs_.insert(h);
			} else {
				hs_.erase(hs_.equal_range(h).first);
				if(h > this->getMaxHeight()) {
					ans.push_back({x, this->getMaxHeight()});
				}
			}
		}

		return ans;
    }
};

int main() {
	// leftPos, rightPos, height
	// buildings: [[1, 3, 2], [2, 5, 3], [5, 7, 3]]
	// skyline: [[1, 2, 2], [2, 7, 3]]
	// ans: [[1, 2], [2, 3], [7, 0]] (key points)
	Solution sol;
	vector<vector<int>> buildings({{1, 3, 2}, {2, 5, 3}, {5, 7, 3}});
	for(vector<int> p : sol.getSkyline(buildings)) {
		printVector(p);
	}

	return 0;
}