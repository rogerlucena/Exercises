#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/*
  Merge the overlapping intervals.

  https://leetcode.com/problems/merge-intervals/description/
*/

// The good idea is to sort the intervals by the start point at the beginning, and then use a stack!

// Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
    void print() {
      cout << "[" << start << ", " << end << "]" << endl;
    }
};

class Solution {
 public:

  bool areOverlapping(Interval &i1, Interval &i2) {
    return i1.end >= i2.start;
  }

  Interval merge2(Interval &i1, Interval &i2) {
    int end = i2.end;
    if(i1.end > i2.end) end = i1.end;
    Interval ans(i1.start, end);
    return ans;
  }

  vector<Interval> merge(vector<Interval>& intervals) {
    if(intervals.size() <= 1) return intervals;

    // Lambda function as my comparison:
    auto cmp = [](const Interval &i1, const Interval &i2) -> bool {return i1.start < i2.start;};
    sort(intervals.begin(), intervals.end(), cmp);

    stack<Interval> s;
    s.push(intervals[0]);
    for (int i=1; i < intervals.size(); ++i) {
      if (areOverlapping(s.top(), intervals[i])) {
        Interval merged = merge2(s.top(), intervals[i]);
        s.pop();
        s.push(merged);
      } else {
        s.push(intervals[i]);
      }
    }

    vector<Interval> ans;
    while (!s.empty()) {
      ans.push_back(s.top());
      s.pop();
    }
    sort(ans.begin(), ans.end(), cmp);
    return ans;
  }
};

int main() {
  vector<Interval> intervals;
  Interval i1(1, 3);
  Interval i2(2, 6);
  Interval i3(8, 10);
  Interval i4(15, 18);

  intervals.push_back(i1);
  intervals.push_back(i3);
  intervals.push_back(i4);
  intervals.push_back(i2);

  cout << "Original intervals:" << endl;
  for (auto i : intervals) i.print();
  cout << "New intervals:" << endl;
  Solution sol;
  auto ans = sol.merge(intervals);
  for (auto i: ans) i.print();

  return 0;
}