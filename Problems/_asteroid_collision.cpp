#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// https://neetcode.io/problems/asteroid-collision/question
// https://leetcode.com/problems/asteroid-collision

// You are given an array asteroids of integers representing asteroids in a row. The indices of the asteriod
// in the array represent their relative position in space.

// For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning
// right, negative meaning left). Each asteroid moves at the same speed.

// Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode.
// If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

// Example:
// Input: asteroids = [2,4,-4,-1]
// Output: [2]

// Constraints:
// 2 <= asteroids.length <= 10,000.
// -1000 <= asteroids[i] <= 1000
// asteroids[i] != 0

// Remember: stack for this type of problems work as a glove.
// O(n) int time and space.
vector<int> asteroidCollision(vector<int>& asteroids) {
	vector<int> ans;

	for (int i = 0; i < asteroids.size();) {
		if (ans.empty() || (ans.back() < 0 || asteroids[i] > 0)) {
			ans.push_back(asteroids[i++]);
			continue;
		}
		if (ans.back() == abs(asteroids[i])) {
			ans.pop_back();
			++i;
		} else if (ans.back() < abs(asteroids[i])) {
			ans.pop_back();
		} else {
			++i;
		}
	}

	return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}