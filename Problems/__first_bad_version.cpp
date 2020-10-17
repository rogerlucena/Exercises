#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/first-bad-version/

// You are a product manager and currently leading a team to develop a new product. Unfortunately, 
// the latest version of your product fails the quality check. Since each version is developed based on 
// the previous version, all the versions after a bad version are also bad.

// Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes 
// all the following ones to be bad.

// You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a function 
// to find the first bad version. You should minimize the number of calls to the API.

// Example:
// Input: n = 5, bad = 4
// Output: 4
// Explanation:
// call isBadVersion(3) -> false
// call isBadVersion(5) -> true
// call isBadVersion(4) -> true
// Then 4 is the first bad version.

// Constraints:
// 1 <= bad <= n <= 2^(31) - 1

// In this problem it is crucial to look at the constraints!! (red flag mistake if not)
// Attention to limits! even +1 already overflow, use l + (r-l)/2 or use long castings (see below)!
int firstBadVersion(int n) {
	int l = 1;
	int r = n;
	while(l < r) {
		int mid = l + (r-l)/2;
		if(isBadVersion(mid)) {
			r = mid;
		} else {
			l = mid+1;
		}
	}

	return l;
}

bool isFirstBadVersion(int el) {
	if(!isBadVersion(el)) {
		return false;
	}
	
	return (el-1 == 0) || !isBadVersion(el-1);
}

int myFirstBadVersion(int n) {
	int mid = 1 + (n-1)/2; // or (long(n) + 1)/2, with a long mid!
	int l = 1;
	int r = n;
	while(!isFirstBadVersion(mid)) {
		if(isBadVersion(mid)) {
			r = mid - 1; 
		} else {
			l = mid + 1;;
		}
		mid = l + (r-l)/2; // or (long(l) + r)/2
	}
	
	return int(mid);
}

bool isBadVersion(int el) {
	return el == 4;
}

int main() {
	cout << "Hello, World!";
	return 0;
}