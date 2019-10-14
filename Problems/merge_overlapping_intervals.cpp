#include <iostream>
#include <vector>
#include <algorithm>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/merge-overlapping-intervals/

// Given a collection of intervals, merge all overlapping intervals.
// For example:
// Given [1,3],[2,6],[8,10],[15,18],
// return [1,6],[8,10],[15,18].
// Make sure the returned intervals are sorted.

// The following solution is O(n log n) in time, n = number of intervals in A

// Definition for an interval.
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

void addInterval(int s, int e, vector<Interval> &ans) {
	Interval it (s, e);
	ans.push_back(it);
}

vector<Interval> merge(vector<Interval> &A) {
	vector<Interval> intervals = vector<Interval>(A);
	if(intervals.size() <= 1) {
		return intervals;
	}
    
	vector<Interval> ans = {};
	auto cmp = [](const Interval &i1, const Interval &i2) -> bool {return i1.start < i2.start;};
	sort(intervals.begin(), intervals.end(), cmp);

	int currStart = intervals[0].start;
	int currEnd = intervals[0].end;
	for(int i = 1; i < intervals.size(); i++) {
		if(currEnd >= intervals[i].start) {
			currEnd = intervals[i].end > currEnd ? intervals[i].end : currEnd;
			continue;
		}
		addInterval(currStart, currEnd, ans);
		currStart = intervals[i].start;
		currEnd = intervals[i].end;
	}
	addInterval(currStart, currEnd, ans);

	return ans;
}

int main() {
	// Given [1,3],[2,6],[8,10],[15,18]
	// return [1,6],[8,10],[15,18]
	Interval i1 = {1, 3};
	Interval i2 = {2, 6};
	Interval i3 = {8, 10};
	Interval i4 = {15, 18};

	vector<Interval> A = {i1, i2, i3, i4};
	vector<Interval> ans = merge(A);

	cout << "Answers:" << endl;
	auto printEl = [](const Interval &i) -> void {cout << "[" << i.start << "," << i.end << "]";};
	printVector(ans, (function<void(const Interval&)>) printEl);

	return 0;
}