#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/non-overlapping-intervals
// https://leetcode.com/problems/non-overlapping-intervals

// Given an array of intervals intervals where intervals[i] = [start_i, end_i], return the minimum number 
// of intervals you need to remove to make the rest of the intervals non-overlapping.

// Note: Intervals are non-overlapping even if they have a common point. For example, [1, 3] and [2, 4] are 
// overlapping, but [1, 2] and [2, 3] are non-overlapping.

// Example 1:
// Input: intervals = [[1,2],[2,4],[1,4]]
// Output: 1

// Constraints:
// 1 <= intervals.length <= 10^5
// intervals[i].length == 2
// -5 * 10^4 <= starti < endi <= 5 * 10^4


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
	return 0;
}