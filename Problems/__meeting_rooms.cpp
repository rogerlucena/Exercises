#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

// https://neetcode.io/problems/meeting-schedule-ii (well explained solution)
// https://leetcode.com/problems/meeting-rooms-ii/
// Remember: for "intervals" problems it is useful to think about sorting (normally by start_time) - same in merge-overlapping-intervals and non-overlapping-intervals (also pasted below).
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
    while (i < starts.size()) {  // be careful and use a "while" here to avoid incrementing "i" when you also increment "j" (gives wrong answer).
        if (starts[i] < ends[j]) {  // note that in the case of equality you decrement the counter first - as wanted (can reuse that room for the new meeting, otherwise could yield a fake max_rooms)
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

// O(n log n) in time and O(n) in space.
int minMeetingRoomsSweepLine(vector<Interval>& intervals) {  // Using "events", Sweep Line algorithm.
	vector<vector<int>> events;

	for (const Interval& i : intervals) {
		events.push_back({i.start, +1});
		events.push_back({i.end, -1});
	}

	sort(events.begin(), events.end());
	// sort in lexicographical order by default (if same number in index 0, compare index 1 and so on, and if all elements equal and eventually one vector is smaller than the other the smaller one goes first (not happening here) - just like strings).
	// this way, in the case of a tie in the timestamp the pair with -1 will show up first - which is what we want to keep track of max_count below.

	int count = 0;
	int max_count = 0;
	for (const vector<int>& e : events) {
		if (e[1] == 1) {
			++count;
		} else {
			--count;
		}
		max_count = max(max_count, count);
	}

	return max_count;
}

// Nice solution using an ordered map in C++ as well: 
// O(n log n) in time and O(n) in space too.
int minMeetingRoomsMap(vector<Interval>& intervals) {
    map<int, int> mp;  // at that timestamp, gives the liquid increment or decrement on the number of rooms used.
    for (auto& i : intervals) {
        ++mp[i.start];
        --mp[i.end];
    }

    int rooms = 0, max_rooms = 0;
    for (const auto& [_, diff] : mp) {
        rooms += diff;
        max_rooms = max(max_rooms, rooms);
    }

    return max_rooms;
}

// Older solution (less clear):
int minMeetingRooms(vector<vector<int>>& intervals) {
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


// More "intervals" problems (sorting by start_time is useful!):

// merge-overlapping-intervals
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());

    int curr_start = intervals[0][0];      
    int curr_end = intervals[0][1];
    vector<vector<int>> ans;
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] <= curr_end) {
            curr_end = max(curr_end, intervals[i][1]);
        } else {
            ans.push_back({curr_start, curr_end});
            curr_start = intervals[i][0];
            curr_end = intervals[i][1];
        }
    }
    ans.push_back({curr_start, curr_end});

    return ans;
}

// non-overlapping-intervals
// Minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());

    int last_end = intervals[0][1];
    int count = 0;
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] < last_end) { // intersection, will necessarily need to remove one of the two - choose the one with largest end then to avoid more future conflicts.
            last_end = min(last_end, intervals[i][1]); // removed the interval with largest end.
            ++count; // increment the count of removed intervals.
        } else {
            last_end = intervals[i][1];
        }
    }

    return count;
}

int main() {
	cout << "Hello, World!";
	return 0;
}