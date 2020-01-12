#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://www.interviewbit.com/problems/longest-increasing-subsequence/

// Find the longest increasing subsequence of a given array of integers, A.

// In other words, find a subsequence of array in which the subsequence’s elements are in strictly increasing order, 
// and in which the subsequence is as long as possible.
// This subsequence is not necessarily contiguous, or unique.
// In this case, we only care about the length of the longest increasing subsequence.

// Constraints:
// 1 <= length(A) <= 2500
// 1 <= A[i] <= 2000

// Example :
// Input 1:
//     A = [1, 2, 1, 5]
// Output 1:
//     3
// Explanation 1:
//     The sequence : [1, 2, 5]

// DP: try to divide into smaller recursive problems, if overlaps -> memoization
// go from right to left, iterate through the elements to the right bigger than "curr" using "memo", 
// save the max size increasing for every element
int lis(const vector<int> &A) {
	unordered_map<int, int> m;

	int longest = 0;
	for(int i = A.size()-1; i >= 0; --i) {
		m[i] = 1;
		for(int j = i+1; j < A.size(); ++j) {
			if(A[i] < A[j]) {
				m[i] = max(m[i], m[j]+1);
			}
		}

		longest = max(longest, m[i]);
	} 

	return longest;
}


int main() {
	cout << "Hello, World!";
	return 0;
}