#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// https://neetcode.io/problems/task-scheduling
// https://leetcode.com/problems/task-scheduler
// Review: use priority_queue to get the most frequent, and also a queue, and remember to pop to not have infinite loop!

// You are given an array of CPU tasks tasks, where tasks[i] is an uppercase english character from A to Z. 
// You are also given an integer n.

// Each CPU cycle allows the completion of a single task, and tasks may be completed in any order.
// The only constraint is that identical tasks must be separated by at least n CPU cycles, to cooldown the CPU.
// Return the minimum number of CPU cycles required to complete all tasks.

// Example 1:
// Input: tasks = ["X","X","Y","Y"], n = 2
// Output: 5
// Explanation: A possible sequence is: X -> Y -> idle -> X -> Y.

// Constraints:
// 1 <= tasks.length <= 1000
// 0 <= n <= 100

// O(m) in time where m is the size of tasks, and remember only 26 different possible tasks so O(1) in space.
int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> frequencies;
    for (char task : tasks) {
        ++frequencies[task];
    }

    auto cmp = [](const pair<char, int>& task_freq1,
                  const pair<char, int>& task_freq2) {
        return task_freq1.second < task_freq2.second;
    };
    priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)>
        max_heap(frequencies.begin(), frequencies.end(), cmp);
    queue<pair<char, int>> cooldown; // task and next_available_time

    int t = 0;
    for (; !max_heap.empty() || !cooldown.empty(); ++t) {
        if (!max_heap.empty()) {
            auto [task, _] = max_heap.top();
            max_heap.pop();
            if (--frequencies[task] > 0) {
                cooldown.push(make_pair(task, t + n));
            }
        } else {
            auto [_, available_at_time] = cooldown.front();
            t = available_at_time;
        }

        if (!cooldown.empty()) {
            auto [task, available_at_time] = cooldown.front();
            if (t >= available_at_time) {
                max_heap.push(make_pair(task, frequencies[task]));
                cooldown.pop();
            }
        }
    }

    return t;
}

int main() {
	vector<char> tasks = {'X','X','Y','Y'}; // ans: 5
    int n = 2;

    cout << "Ans: " << leastInterval(tasks, n) << endl;

	return 0;
}