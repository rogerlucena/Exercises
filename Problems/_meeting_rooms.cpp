#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// https://leetcode.com/problems/meeting-rooms-ii/

// Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei),
// find the minimum number of conference rooms required.

// Example 1:
// Input: [[0, 30],[5, 10],[15, 20]]
// Output: 2

// Example 2:
// Input: [[7,10],[2,4]]
// Output: 1
// NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.

int minMeetingRooms(vector<vector<int>> &intervals) {
	if(intervals.empty()) {
		return 0;
	}

	sort(intervals.begin(), intervals.end(), [](const vector<int>& i1, const vector<int>& i2) {
		return i1[0] < i2[0];
	});

	priority_queue<int, vector<int>, greater<int>> endTimes;
	endTimes.push(intervals[0][1]);
	for(int i = 1; i < intervals.size(); ++i) {
		vector<int> interval = intervals[i];
		if(interval[0] >= endTimes.top()) {
			endTimes.pop();
		}
		endTimes.push(interval[1]);
	}

	return endTimes.size();
}

int main() {
	cout << "Hello, World!";
	return 0;
}