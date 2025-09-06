#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/minimum-time-difference (Google problem)
// Remember: could have sorted the times (in minutes) - O(N log N), or used bucket sort as below O(N) in time.
// For more search "Circular Array" inside "My Notes".

// Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between 
// any two time-points in the list.

// Example 1:
// Input: timePoints = ["23:59","00:00"]
// Output: 1

// Example 2:
// Input: timePoints = ["00:00","23:59","00:00"]
// Output: 0

// Constraints:
// 2 <= timePoints.length <= 2 * 104
// timePoints[i] is in the format "HH:MM".

// "HH:MM" format
int convertToMinutes(const string& time) {
    int hours = stoi(time.substr(0, 2));
    int minutes = stoi(time.substr(3, 2));

    return hours * 60 + minutes;
}

int findMinDifference(vector<string>& timePoints) {
    vector<int> buckets(24 * 60, 0);
    for (const string& time : timePoints) {
        ++buckets[convertToMinutes(time)];
    }

    int first_index = -1;
    int last_index = -1;
    int prev_index = -1;
    int min_diff = INT_MAX;
    for (int i = 0; i < buckets.size(); ++i) {
        if (!buckets[i]) {
            continue;
        }
        if (buckets[i] > 1) {
            return 0;
        }

        if (first_index == -1) {
            first_index = i;
        }
        if (prev_index != -1) {
            min_diff = min(min_diff, i - prev_index);
        }
        
        prev_index = i;
        last_index = i;
    }

    min_diff = min(min_diff, 24 * 60 - last_index + first_index);  // circular array.
    return min_diff;
}

int main() {
	cout << "Hello, World!";
	return 0;
}