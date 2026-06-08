#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/boats-to-save-people
// https://leetcode.com/problems/boats-to-save-people

// You are given an integer array people where people[i] is the weight of the ith person, and an
// infinite number of boats where each boat can carry a maximum weight of limit. Each boat carries at most
// two people at the same time, provided the sum of the weight of those people is at most limit.
// Return the minimum number of boats to carry every given person.

// Example:
// Input: people = [5,1,4,2], limit = 6
// Output: 2
// Explanation:
// First boat [5,1].
// Second boat [4,2].

// Constraints:
// 1 <= people.length <= 50,000
// 1 <= people[i] <= limit <= 30,000

// Remember: if only max two people in the same boat, we want to pair the heaviest (who has to go in a boat at some time
// anyway) with the lightest each time.
// Greedy + two pointers + sorting.
// O(n log n) in time and O(1) in space (depending on the sorting algorithm).
int numRescueBoatsFirstVersion(vector<int>& people, int limit) {
    sort(people.begin(), people.end());  // IntroSort (variation of quicksort) used here that is considered in-place (O(log n) worst case in space), while standard quicksort worst case can be O(N) in space (recursion stack with bad pivots - if not using Tail Recursive Optimization for the larger half call).
	int i = 0, j = people.size() - 1;  // safe "-1" here since "size >= 1".
	int boats = 0;

	while (i < j) {
		if (people[i] + people[j] <= limit) {
			++i;
		}
		--j;
		++boats;
	}
	if (i == j) {
		++boats;
	}

	return boats;
}

// Improvement: O(n) in time with counting sort, O(m) in space where "m" is the maximum element in "people".
// Leverage the fact that max_element inside "people" is limited.
int numRescueBoats(vector<int>& people, int limit) {
	int max_weight = *max_element(people.begin(), people.end());  // O(n) in time.
	vector<int> count(max_weight + 1, 0);
	int boats = 0;

	for (int weight : people) {
		++count[weight];
	}

	int i = 0, j = max_weight;
	while (i < j) {  // do as below or rebuild "people" to be sorted now using "count" -> and then proceed as above. 
		if (count[i] == 0) {
			++i;
			continue;
		}
		if (count[j] == 0) {
			--j;
			continue;
		}

		if (i + j <= limit) {
			int departing_boats = min(count[i], count[j]);
			boats += departing_boats;
			count[i] -= departing_boats;
			count[j] -= departing_boats;
		} else {
			boats += count[j];
			count[j] = 0;
		}
	}

	if (i == j) {
		if (2 * i <= limit) {
			boats += count[i] / 2;
			boats += count[i] % 2;
		} else {
			boats += count[i];
		}
	}

	return boats;
}

int main() {
	cout << "Hello, World!";
	return 0;
}