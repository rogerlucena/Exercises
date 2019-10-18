#include <iostream>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/merge-intervals/

// Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
// You may assume that the intervals were initially sorted according to their start times.

// Definition for an interval.
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

// Tip: remember that, given [a, b] and [c, d], if max(a,c) > min(b,d) then do not overlap
bool overlap(Interval i1, Interval i2) {
	return !(max(i1.start, i2.start) > min(i1.end, i2.end));
}

auto printEl = [](const Interval &i) -> void {cout << "[" << i.start << "," << i.end << "]";};

vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
	vector<Interval> ans = {};
	if(newInterval.start > newInterval.end) {
		int tmp = newInterval.start;
		newInterval.start = newInterval.end;
		newInterval.end = tmp;
	}
	
	// printEl(newInterval);
	// cout << endl;

	if(intervals.size() == 0) {
		ans.push_back(newInterval);
		return ans;
	}

	int iOverlap = -1, jOverlap = -1;
	// cout << iOverlap << " --- " << jOverlap << endl;

	for (int i = 0; i < intervals.size(); ++i) {
		if(overlap(intervals[i], newInterval)) {
			if(iOverlap == -1) {
				iOverlap = jOverlap = i;
			}
			else {
				jOverlap = i;
			}
		}
	}

	if(iOverlap == -1) {
		if(newInterval.start < intervals[0].start) {
			ans.push_back(newInterval);
		}
		for (int i = 0; i < intervals.size(); ++i) {
			if(i != 0 && newInterval.start < intervals[i].start && newInterval.start > intervals[i-1].start) {
				ans.push_back(newInterval);
			}
			ans.push_back(intervals[i]);
		}
		if(newInterval.start > intervals[intervals.size()-1].start) {
			ans.push_back(newInterval);
		}
	} else {
		newInterval.start = min(newInterval.start, intervals[iOverlap].start);
		newInterval.end = max(newInterval.end, intervals[jOverlap].end);
		for (int i = 0; i < intervals.size(); ++i) {
			if(i < iOverlap || i > jOverlap) {
				ans.push_back(intervals[i]);
			} else {
				ans.push_back(newInterval);
				i = jOverlap;
			}
		}
	}

	return ans;
}

int main() {
	// intervals: {[1,3], [6,9]}, newInterval: [2, 5]
	// answer: {[1,5], [6,9]}
	Interval i1(1, 3); 
	Interval i2(6, 9);
	vector<Interval> intervals = {i1, i2};
	Interval newInterval(2, 5);

	vector<Interval> ans = insert(intervals, newInterval);
	cout << "Answer:" << endl;
	printVector(ans, (function<void(const Interval&)>) printEl);

	return 0;
}