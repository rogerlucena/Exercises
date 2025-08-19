#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// https://neetcode.io/problems/meeting-schedule-ii (well explained solution)
// https://leetcode.com/problems/meeting-rooms-ii/
// Remember: for min number of rooms, nice to have all start times sorted in one vector and end times sorted in 
// the other, and use two pointers. 
// When using two indexes use a "while" and not "for" to avoid incrementing one index when also incremented the other as below.
// Ask "Sweep Line Algorithm for Coding Interviews" on ChatGPT for more examples of problems using this idea of
// events {start, +1} or {end, -1} keeping a count and max_count.

// Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei),
// find the minimum number of conference rooms required.

// Example 1:
// Input: [[0, 30],[5, 10],[15, 20]]
// Output: 2

// Example 2:
// Input: [[7,10],[2,4]]
// Output: 1
// NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

// Neetcode solution:
// O(N log N) in time and O(N) in space.
int minMeetingRooms(vector<Interval>& intervals) {
    vector<int> starts;
    vector<int> ends;

    for (const Interval& interval : intervals) {
        starts.push_back(interval.start);
        ends.push_back(interval.end);
    }

    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    int curr_rooms = 0, max_rooms = 0;
    int i = 0, j = 0;
    while (i < starts.size()) { // be careful and use a "while" here to avoid incrementing "i" when you also increment "j" (gives wrong answer).
        if (starts[i] < ends[j]) {
            ++curr_rooms;
            ++i;
        } else {
            --curr_rooms;
            ++j;
        }

        max_rooms = max(max_rooms, curr_rooms);
    }

    return max_rooms;
}

// Older solution (less clear):
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

	return endTimes.size(); // conflicting meetings will not have a pop for the push, by the end the max number of conflicting meetings will also be recorded on this size here.
}

int main() {
	cout << "Hello, World!";
	return 0;
}