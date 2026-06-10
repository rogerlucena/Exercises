#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/find-k-closest-elements
// https://leetcode.com/problems/find-k-closest-elements

// You are given a sorted integer array arr, two integers k and x, return the k closest integers to x
// in the array. The result should also be sorted in ascending order.
// An integer a is closer to x than an integer b if:

// |a - x| < |b - x|, or
// |a - x| == |b - x| and a < b

// Example 1:
// Input: arr = [2,4,5,8], k = 2, x = 6
// Output: [4,5]

// Example 2:
// Input: arr = [2,3,4], k = 3, x = 1
// Output: [2,3,4]

// Constraints:
// 1 <= k <= arr.length <= 10,000.
// -10,000 <= arr[i], x <= 10,000
// arr is sorted in ascending order.

// Nice Neetcode solution (adapted binary search):
// O(log(n − k) + k) in time and O(k) in space.
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
	int l = 0, r = arr.size() - k;
	while (l < r) {
		int m = l + (r - l) / 2;  // the candidate is the interval [m, m+k) -> then compare dist(arr[m]) to dist(arr[m+k]) to see if interval should move right or not.
		if (x - arr[m] > arr[m + k] - x) {  // if true the window is too far left, so set l = m + 1.
			l = m + 1;
		} else {
			r = m;
		}
	}

	return vector<int>(arr.begin() + l, arr.begin() + l + k);
}

// My solution below:
// O(log n + k) in time and O(k) in space (create output array).
bool isCloser(int i, int j, int x, const vector<int>& arr) {
	if (i < 0) {
		return false;
	}
	if (j >= arr.size()) {
		return true;
	}
	
	if (abs(arr[i] - x) <= abs(arr[j] - x)) {
		return true;
	}
	
	return false;
}

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
	vector<int>::iterator ub = upper_bound(arr.begin(), arr.end(), x);
    int j = ub - arr.begin();
	int i = j - k;
	// Candidate interval: [i, j)

	while (!isCloser(i, j, x, arr)) {
		++i;
		++j;
	}

	vector<int> ans (arr.begin() + i, arr.begin() + j);
	return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}