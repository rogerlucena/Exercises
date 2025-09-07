#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii (asked on Exponent/Pramp from a Google guy on Sep 6 2025)
// https://www.tryexponent.com/practice/prepare/remove-duplicates-in-string
// Remember: consider stack on these kind of problems, and here a stack of pairs {char, count} 
// already enables a much cleaner solution.

// You are given a string s and an integer k, a k duplicate removal consists of choosing k adjacent and equal letters 
// from s and removing them, causing the left and the right side of the deleted substring to concatenate together.

// We repeatedly make k duplicate removals on s until we no longer can.

// Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.

// Example 1:
// Input: s = "abcd", k = 2
// Output: "abcd"
// Explanation: There's nothing to delete.

// Example 2:
// Input: s = "deeedbbcccbdaa", k = 3
// Output: "aa"
// Explanation: 
// First delete "eee" and "ccc", get "ddbbbdaa"
// Then delete "bbb", get "dddaa"
// Finally delete "ddd", get "aa"

// Example 3:
// Input: s = "pbbcggttciiippooaais", k = 2
// Output: "ps"
 
// Constraints:
// 1 <= s.length <= 105
// 2 <= k <= 104
// s only contains lowercase English letters.

// Nice/clean website solution, use a vector as stack already adding the pair {char, count} (instead of two separate stacks as below).
// Linear in time and space.
string removeDuplicates(string s, int k) {
    vector<pair<char, int>> st;
    for (char c : s) {
        if (!st.empty() && st.back().first == c) {
            ++st.back().second;
        } else {
            st.push_back({c, 1});
        }
        if (st.back().second == k) { // If reach enough k duplicate letters -> then remove.
            st.pop_back();
        }
    }

    string ans;
    for (const pair<char, int>& p : st) {
        ans.append(p.second, p.first);
    }
    return ans;
}

// My solution (more complex below):
string removeDuplicates(string s, int k) {
    stack<char> st;
    stack<int> counts;

    int count = 0;
    for (char c : s) {
        if (st.empty()) {
            ++count;
            st.push(c);
            continue;
        }

        if (c != st.top()) {
            counts.push(count);
            count = 1;
            st.push(c);
        } else {
            ++count;
            if (count < k) {
                st.push(c);
                continue;
            } 

            // count == k
            for (int i = 1; i <= k - 1; ++i) {
                st.pop();
            }
            if (!counts.empty()) {
                count = counts.top();
                counts.pop();
            } else {
                count = 0;
            }
        }
    }

    string ans;
    while (!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }

    reverse(ans.begin(), ans.end());
    return ans;
}
// It follows the following logic after going through the example s = "deeedbbcccbdaa", k = 3, output: "aa"
/*
if st empty
++count, push st

different to top
push to counts, count = 1, push st

equal to top
++count
if count < k: push st
if count == k: pop k-1 from st, count = counts.top(), counts.pop() if counts not empty - else count = 0
*/

int main() {
	cout << "Hello, World!";
	return 0;
}