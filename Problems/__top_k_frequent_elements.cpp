#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// https://leetcode.com/problems/top-k-frequent-elements/description/

// Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

// Example 1:
// Input: nums = [1,1,1,2,2,3], k = 2
// Output: [1,2]

// Example 2:
// Input: nums = [1], k = 1
// Output: [1]
 
// Constraints:
// 1 <= nums.length <= 10^5
// -10^4 <= nums[i] <= 10^4
// k is in the range [1, the number of unique elements in the array].
// It is guaranteed that the answer is unique.


// Remember to use bucket sort sometimes as well (frequencies are limited till N)! Or Priority Queue below!

// Aim for O(N) in time and O(N) in space
vector<int> topKFrequent(vector<int>& nums, int k) {
	int n = nums.size();
	vector<vector<int>> buckets(n + 1); // always N in space, which on leetcode resulted on this solution being a bit worse in space on some cases than the one below.
	
	unordered_map<int, int> frequencies;
	for (int num : nums) {
		frequencies[num]++;
	}

	for (const auto& [num, freq] : frequencies) {
		buckets[freq].push_back(num);
	}

	vector<int> top_k_frequent;
	for (int freq = n; freq > 0; --freq) {
		for (int num : buckets[freq]) {
			top_k_frequent.push_back(num);
			if (top_k_frequent.size() == k) {
				return top_k_frequent;
			}
		}
	}

	return top_k_frequent;
}

// Solution O(N log K) in time and O(N + K) in space
vector<int> topKFrequentPq(vector<int>& nums, int k) {
	unordered_map<int, int> freqs;
	for (int num : nums) {
		freqs[num]++;
	}
	
	auto cmp = [](const pair<int, int>& num_freq1, const pair<int, int>& num_freq2){return num_freq1.second > num_freq2.second;};
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> num_freq_pq;

	for (pair<int, int> num_freq : freqs) {
		if (num_freq_pq.size() < k) {
			num_freq_pq.push(num_freq);
			continue;
		}
		if (num_freq.second > num_freq_pq.top().second) {
			num_freq_pq.pop();
			num_freq_pq.push(num_freq);
		}
	}

	vector<int> top_k_frequent;
	for (; !num_freq_pq.empty(); num_freq_pq.pop()) {
		top_k_frequent.push_back(num_freq_pq.top().first);
	}

	return top_k_frequent;
}

int main() {
	// cout << "Hello, World!";
	vector<int> nums = {1,2,2,3,3,3};
	int k = 2;

    // Output: [2,3]
	vector<int> top_k_frequent = topKFrequent(nums, k);
	for (int el : top_k_frequent) {
		cout << el << " ";
	}

	return 0;
}