#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://neetcode.io/problems/trapping-rain-water (good explanation for solution there - https://youtu.be/ZI2z5pq0TqA?si=vA3JzO2ZA98hhHLx)
// https://leetcode.com/problems/trapping-rain-water
// Hard Leetcode level - two pointers in a less immediate way.

// You are given an array of non-negative integers height which represent an elevation map. Each value height[i] represents the height of 
// a bar, which has a width of 1.
// Return the maximum area of water that can be trapped between the bars.

// Example:
// Input: height = [0,2,0,3,1,0,1,3,2,1]
// Output: 9

// Constraints:
// 1 <= height.length <= 1000
// 0 <= height[i] <= 1000

// Two pointers below, O(1) in extra space and O(N) in time.
// Could think of building two auxiliar vectors too, max_left and max_right to keep the max_left and right for each position, but O(N) in extra space.
int trap(vector<int>& height) {
	if (height.size() <= 2) {
		return 0;
	}

	int res = 0;
	int left = 0, right = height.size() - 1;
	int max_left = height[left], max_right = height[right];
	while (left < right) {
		if (max_left <= max_right) { // the max_left value is precise for the left pointer and min(max_left, max_right) will always be max_left here for 'left' - other values to the left of the current max_right could only increase max_right and max_left already will be smaller than all of them.
			++left;
			res += max(max_left - height[left], 0); // could permutate this line with the one below and avoid this max operation here, but leaving like this for clarity.
			max_left = max(max_left, height[left]);
		} else {
			--right;
			res += max(max_right - height[right], 0);
			max_right = max(max_right, height[right]);
		}
	}

	return res;
}

// Requires O(N) extra in space, O(N) in time but slower on Leetcode as well (this is faster than 20% and above is faster than 100%).
int trapWithStack(vector<int>& height) {
	if (height.size() <= 2) {
		return 0;
	}

	stack<int> max_right_index; // index with maximum height to the right.
    for (int i = height.size() - 1; i > 1; --i) {
		if (max_right_index.empty() || height[i] > height[max_right_index.top()]) {
			max_right_index.push(i);
		}
    }

    int max_left_index = 0; // index with maximum height to the left.
	int res = 0;
	for (int i = 1; i < height.size() - 1; ++i) {
		if (i == max_right_index.top()) {
			max_right_index.pop();
		}
		res += max(min(height[max_left_index], height[max_right_index.top()]) - height[i], 0);
		max_left_index = height[i] > height[max_left_index] ? i : max_left_index;
	}

	return res;
}


int main() {
	// Clarifying multiple initialization below:
	int a, b = 2; // b is 2 and a is garbage (and random each call, do not assume it is 0 !)

	cout << "a = " << a << ", b = " << b << endl;

	return 0;
}