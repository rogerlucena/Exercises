#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://leetcode.com/problems/car-fleet
// https://neetcode.io/problems/car-fleet

// There are n cars traveling to the same destination on a one-lane highway.
// You are given two arrays of integers position and speed, both of length n.

// position[i] is the position of the ith car (in miles)
// speed[i] is the speed of the ith car (in miles per hour)
// The destination is at position target miles.

// A car can not pass another car ahead of it. It can only catch up to another car and then drive at the same 
// speed as the car ahead of it.
// A car fleet is a non-empty set of cars driving at the same position and same speed. A single car is also considered 
// a car fleet.

// If a car catches up to a car fleet the moment the fleet reaches the destination, then the car is considered to 
// be part of the fleet.
// Return the number of different car fleets that will arrive at the destination.

// Example 1:
// Input: target = 10, position = [1,4], speed = [3,2]
// Output: 1
// Explanation: The cars starting at 1 (speed 3) and 4 (speed 2) become a fleet, meeting each other at 10, the destination.

// Example 2:
// Input: target = 10, position = [4,1,0,7], speed = [2,2,1,1]
// Output: 3
// Explanation: The cars starting at 4 and 7 become a fleet at position 10. The cars starting at 1 and 0 never catch up to the car ahead of them. Thus, there are 3 car fleets that will arrive at the destination.

// Constraints:
// n == position.length == speed.length.
// 1 <= n <= 1000
// 0 < target <= 1000
// 0 < speed[i] <= 100
// 0 <= position[i] < target
// All the values of position are unique.

// Interesting, put position and speed together in pairs, sort with rbegin from the end, see that
// the arrival time of each fleet is determined by the car starting closest to target of that fleet.
// Stack below is easier to understand, but no need to keep a entire stack by the end.
int carFleet(int target, vector<int>& position, vector<int>& speed) {
	vector<pair<int, int>> position_speed;
	for (int i = 0; i < position.size(); ++i) {
		position_speed.push_back({position[i], speed[i]}); // good idea to put position and speed together in pairs before sorting.
	}

	sort(position_speed.rbegin(), position_speed.rend()); // way to sort in decreasing order regarding the position, could use a greater comparator as well.

	double prev_time;
	int fleets = 0;
	for (const pair<int, int>& p : position_speed) {
		double t = (double)(target - p.first) / p.second; // remember to convert to double here (otherwise division of ints)! 
		if (fleets == 0 || t > prev_time) { // we get a new fleet.
			++fleets;
			prev_time = t; // the car closest to target in the fleet termines the arrival time of the entire fleet.
		}
	}

	return fleets;
}

int carFleetStack(int target, vector<int>& position, vector<int>& speed) {
	vector<pair<int, int>> position_speed;
	for (int i = 0; i < position.size(); ++i) {
		position_speed.push_back({position[i], speed[i]});
	}

	sort(position_speed.rbegin(), position_speed.rend()); // way to sort in decreasing order regarding the position, could use a greater comparator as well.

	stack<double> times_to_arrive;
	for (const pair<int, int>& p : position_speed) {
		double t = (double)(target - p.first) / p.second; // remember to convert to double here (otherwise division of ints)! 
		if (times_to_arrive.empty() || t > times_to_arrive.top()) {
			times_to_arrive.push(t);
		}
	}

	return times_to_arrive.size();
}

// Solution initializing lane with the target size, not necesserily faster than above but always worse in memory on Leetcode.
int carFleetWorseMemory(int target, vector<int>& position, vector<int>& speed) {
    vector<double> lane(target, 0.0);
    for (int i = 0; i < position.size(); ++i) {
        lane[position[i]] = (double)(target - position[i]) / speed[i];
    }

	int fleets = 0;
	double prev_time = 0.0;
	for (int i = target - 1; i >= 0; --i) {
		if (lane[i] > prev_time) {
			++fleets;
			prev_time = lane[i];
		}
	}

	return fleets;
}

int main() {
	cout << "Hello, World!";
	return 0;
}