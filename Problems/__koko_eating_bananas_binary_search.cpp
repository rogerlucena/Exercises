#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// https://leetcode.com/problems/koko-eating-bananas
// https://neetcode.io/problems/eating-bananas
// Quick review: think about getting an upper bound and then doing a binary search over the possible values.

// You are given an integer array piles where piles[i] is the number of bananas in the ith pile. You are also given an integer h, which 
// represents the number of hours you have to eat all the bananas.
// You may decide your bananas-per-hour eating rate of k. Each hour, you may choose a pile of bananas and eats k bananas from that pile. 
// If the pile has less than k bananas, you may finish eating the pile but you can not eat from another pile in the same hour.
// Return the minimum integer k such that you can eat all the bananas within h hours.

// Example 1:
// Input: piles = [1,4,3,2], h = 9
// Output: 2
// Explanation: With an eating rate of 2, you can eat the bananas in 6 hours. With an eating rate of 1, you would need 10 hours to eat
// all the bananas (which exceeds h=9), thus the minimum eating rate is 2.

// Example 2:
// Input: piles = [25,10,23,4], h = 4
// Output: 25

// Constraints:
// 1 <= piles.length <= 1,000
// piles.length <= h <= 1,000,000
// 1 <= piles[i] <= 1,000,000,000


// O(n log m) where m is the max value in piles.
int minEatingSpeed(vector<int>& piles, int h) {
	int l = 1;
	int r = *max_element(piles.begin(), piles.end()); // upper bound for speed k - minimum of 1 hour for each pile.
	int ans = r;

	// Binary search for 1 to max_element to find minimum speed to finish piles in h hours.
	while (l <= r) { // the valid search interval is [l, r].
        int k = l + (r - l) / 2;

		long total_time = 0; // pay attention in constraints, time can go until 10^12.
		for (int pile : piles) {
            total_time += ceil((static_cast<double>(pile)) / k); // or "(pile + k - 1) / k" also works.
			// total_time += (pile + k - 1) / k; // faster than cast and ceil above.
        }

		if (total_time <= h) { // this k is fast enough, keeps track updating ans and searching for slower speeds.
			ans = k; // guaranteed that the best k will be seen here given the way the search is conducted.
			r = k - 1;
		} else {
			l = k + 1;
		}
    }

	return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}