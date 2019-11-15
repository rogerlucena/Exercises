#include <iostream>
#include <vector>
#include <queue>

using namespace std;
// https://leetcode.com/problems/course-schedule-iii/
// (Hard. Different approaches: DP, priority_queue, incrementally improving)

// There are n different online courses numbered from 1 to n. Each course has some 
// duration(course length) t and closed on dth day. A course should be taken continuously for t days 
// and must be finished before or on the dth day. You will start at the 1st day.
// Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be taken.

// Example in main()

// Note:
// The integer 1 <= d, t, n <= 10,000.
// You can't take two courses simultaneously.

// Solution with a priority_queue
// O(n log n) in time and O(n) in space
// Accepted as well
int scheduleCourse(vector<vector<int>> &courses) {
	if(courses.size() == 0) {
		return 0;
	}

    auto cmp = [](const vector<int> &a, const vector<int> &b) -> bool {return a[1] < b[1];};
	sort(courses.begin(), courses.end(), cmp);

	auto cmp2 = [](const vector<int> &a, const vector<int> &b) -> bool {return a[0] < b[0];};
	priority_queue <vector<int>, vector<vector<int>>, decltype(cmp2)> q(cmp2, {}); // could use only the durations as well

	int timePassed = 0;
	for (vector<int> c : courses) {
		if (timePassed + c[0] <= c[1]) {
			q.push(c);
			timePassed += c[0];
		} else if (!q.empty() && q.top()[0] > c[0]) {
			timePassed += c[0] - q.top()[0];
			q.pop();
			q.push(c);
		}
	}

	return q.size();
}

// Website optmized iterative solution
// O(n*count) in time and O(1) in space (count is the answer)
// First one accepted
int oldScheduleCourse3(vector<vector<int>> &courses) {
	if(courses.size() == 0) {
		return 0;
	}

    auto cmp = [](const vector<int> &a, const vector<int> &b) -> bool {return a[1] < b[1];};
	sort(courses.begin(), courses.end(), cmp);

	int time = 0, count = 0;
	for (int i = 0; i < courses.size(); i++) {
		if (time + courses[i][0] <= courses[i][1]) {
			time += courses[i][0];
			courses[count++] = courses[i];
		} else {
			int max_i = i;
			for (int j = 0; j < count; j++) {
				if (courses[j][0] > courses[max_i][0])
					max_i = j;
			}
			if (courses[max_i][0] > courses[i][0]) {
				time += courses[i][0] - courses[max_i][0];
				courses[max_i] = courses[i];
			}
		}
	}

	return count;
}

// Website iterative solution
// O (n^2) in time and O(1) in space
int oldScheduleCourse2(vector<vector<int>> &courses) {
	if(courses.size() == 0) {
		return 0;
	}

    auto cmp = [](const vector<int> &a, const vector<int> &b) -> bool {return a[1] < b[1];};
	sort(courses.begin(), courses.end(), cmp);

	int time = 0, count = 0;
	for (int i = 0; i < courses.size(); i++) {
		if (time + courses[i][0] <= courses[i][1]) {
			time += courses[i][0];
			count++;
		} else {
			int max_i = i;
			for (int j = 0; j < i; j++) {
				if (courses[j][0] > courses[max_i][0])
					max_i = j;
			}
			if (courses[max_i][0] > courses[i][0]) {
				time += courses[i][0] - courses[max_i][0];
			}
			courses[max_i][0] = -1;
		}
	}

	return count;
}

// DP approach below (still time limit exceeded)
// Time complexity : O(n*d)O(n*d).
// Space complexity : O(n*d)O(n*d).
int scheduleCourseHelper(vector<vector<int>> &courses, int i, int timePassed, vector<vector<int>> &m) {
	if(i == courses.size() || timePassed >= courses[i][1]) {
		return 0;
	}

	if(m[i][timePassed] != -1) {
		return m[i][timePassed];
	}

	// Without ith course
	m[i][timePassed] = scheduleCourseHelper(courses, i+1, timePassed, m);

	if(timePassed + courses[i][0] <= courses[i][1]) {
		m[i][timePassed] = max(m[i][timePassed], 1 + scheduleCourseHelper(courses, i+1, timePassed + courses[i][0], m));
	}

	return m[i][timePassed];
}

// Each course: pair (t, d) - time (duration) and deadline to finish
int oldScheduleCourse1(vector<vector<int>> &courses) {
	if(courses.size() == 0) {
		return 0;
	}

    auto cmp = [](const vector<int> &a, const vector<int> &b) -> bool {return a[1] < b[1];};
	sort(courses.begin(), courses.end(), cmp);

	int maxDeadline = courses[courses.size()-1][1];
	vector<vector<int>> m(courses.size(), vector<int>(maxDeadline, -1));
	return scheduleCourseHelper(courses, 0, 0, m);
}

int main() {
	vector<vector<int>> courses = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}}; // ans: 3
	cout << "Answer: " << scheduleCourse(courses) << endl;

	return 0;
}