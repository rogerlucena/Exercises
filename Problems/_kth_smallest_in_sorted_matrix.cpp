#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/

// Given an n x n matrix where each of the rows and columns are sorted in ascending order, 
// return the kth smallest element in the matrix.

// Note that it is the kth smallest element in the sorted order, not the kth distinct element.

// Example:
// Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
// Output: 13
// Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13

// Being X = min(N, K), we have O(X log X + K log X) in time, O(X) in space
int kthSmallest(vector<vector<int>>& matrix, int k) {
	int n = matrix.size();
	auto cmp = [](const vector<int>& v1, const vector<int>& v2) {return v1[0] > v2[0];};
	priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> minHeap(cmp);
	for(int i = 0; i < min(n, k); ++i) {
		minHeap.push({matrix[i][0], i, 0});
	}

	for(int i = 1; i <= k; ++i) {
		vector<int> el = minHeap.top();
		minHeap.pop();
		// cout << el[0] << " ";
		if(i == k) {
			return el[0];
		}

		int row = el[1];
		int col = el[2];
		if(col + 1 < n) {
			minHeap.push({matrix[row][col+1], row, col+1});
		}
	}

	return -1;
}

// There is another solution there, doing a binary search over the matrix:
// - Algorithm:
// Start the binary search with start = matrix[0][0] and end = matrix[N-1][N-1]
// Find the middle of the start and the end. This middle number is NOT necessarily an element in the matrix.
// Count all the numbers smaller than or equal to middle in the matrix. As the matrix is sorted, we can do this
// in O(N+N). Note that this is determining the size of the left-half of the array (start at [n-1][0], compare to mid, then go up or right).
// While counting, we need to keep track of the smallest number greater than the middle (let’s call it R) and at the same time the
// biggest number less than or equal to the middle (let’s call it L). These two numbers will be used to adjust the number range for
// the binary search in the next iteration.
// If the count is equal to K, L will be our required number as it is the biggest number less than or equal to the middle, and is 
// definitely present in the matrix.
// If the count is less than K, we can update start = R to search in the higher part of the matrix
// If the count is greater than K, we can update end = L to search in the lower part of the matrix in the next iteration.
// - Complexity:
// O(N log(Max-Min)), Max-Min is the size of our search space, and O(N) because it is the cost to count the size of left-half array 
// each time.

int main() {
	vector<vector<int>> matrix1 = {{1,5,9},
								  {10,11,13},
								  {12,13,15}}; // ans: 13
	int k1 = 8;

	vector<vector<int>> matrix2 = {{-5}}; // ans: -5
	int k2 = 1;

	vector<vector<int>> matrix = {{1,3,5},
								  {6,7,12},
								  {11,14,14}}; // ans: 5
	int k = 3;

	int ans = kthSmallest(matrix, k);
	cout << "Answer: " << ans << endl;
	return 0;
}