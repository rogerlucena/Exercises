#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/subarray-sum-equals-k/

// Given an array of integers and an integer k, you need to find the total number of continuous 
// subarrays whose sum equals to k.

// Example:
// Input:nums = [1,1,1], k = 2
// Output: 2

// Note:
// The length of the array is in range [1, 20,000].
// The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].

// Cool O(N) solution, use a hash map to keep track of previous accumulated sums.
int subarraySum(vector<int> &nums, int k) {
	int count = 0;
	int currSum = 0;
	unordered_map<int, int> prevSums;
	prevSums[0] = 0;
	for(int i = 0; i < nums.size(); ++i) {
		currSum += nums[i];
		if(currSum == k) {
			count += 1 + prevSums[0];
		} else if(prevSums.find(currSum - k) != prevSums.end()) {
			count += prevSums[currSum - k];
		}

		if(prevSums.find(currSum) != prevSums.end()) {
			prevSums[currSum] += 1;
		} else {
			prevSums[currSum] = 1;
		}
	}

	return count;
}

int main() {
	vector<int> nums = {1, 1, 1}; // ans: 2
	int k = 2;

	cout << "Answer: " << subarraySum(nums, k) << endl;
	return 0;
}