#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/find-the-duplicate-number/ (solution explains hare tortoise visually there)
// also explained here: https://www.geeksforgeeks.org/dsa/find-any-one-of-the-multiple-repeating-elements-in-read-only-array-set-2/
// https://neetcode.io/problems/find-duplicate-integer
// https://www.interviewbit.com/problems/find-duplicate-in-array

// Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.
// There is only one repeated number in nums, return this repeated number.
// You must solve the problem without modifying the array nums and uses only constant extra space.

// Example 1:
// Input: nums = [1,3,4,2,2]
// Output: 2

// Example 2:
// Input: nums = [3,1,3,4,2]
// Output: 3
 
// Constraints:
// 1 <= n <= 105
// nums.length == n + 1
// 1 <= nums[i] <= n
// All the integers in nums appear only once except for precisely one integer which appears two or more times.

// Hare and Tortoise solution - O(N), and O(1) in space - Floyd's Cycle Detection algorithm.
// Neetcode considers it not a medium but a hard problem that even Floyd would not solve in 30 min without seeing it before.
int findDuplicate(vector<int>& nums) {
	int hare = nums[0]; // "fast" pointer
	int tortoise = nums[0]; // "slow" pointer
	do {
		hare = nums[nums[hare]];
		tortoise = nums[tortoise];
	} while (hare != tortoise); // they meet each other inside the cycle but not necessarily at the point the cycle begins.

	tortoise = nums[0]; // now they will meet at the point the cycle begins with v = 1 for each. Or create/name it a "slow2" pointer for clarity.
	while (hare != tortoise) {
		hare = nums[hare];
		tortoise = nums[tortoise];
	}

	return hare;
}
// Note: if in a linked list, also needs to check that "fast" and "fast->next" are not nullptr.
// Proof of Hare and Tortoise to find the entrance point of the cycle:
// v.t, 2v.t
// e (distance to start cycle)
// (2v.t-e) % C == (v.t-e) % C => v.t is congruent to 0 modulus C (size of cycle).
// e/v time after tortoise start from 0 again
// position of hare will be: (e/v * v) + (v.t-e) == v.t modulus C which is 0 (entrance of the cycle as we wanted).

// Other nice/genius idea (in-place, but would have to write on input = use the array itself as a hash map "seen" using the negative sign to flag number already seen):
// traverse the list for i=0 to n-1 elements {
//   check for sign of A[abs(A[i])] ;
//   if positive then
//      make it negative by   A[abs(A[i])]=-A[abs(A[i])];
//   else  // i.e., A[abs(A[i])] is negative
//      this   element (ith element of list) is a repetition
// }
// From: https://www.geeksforgeeks.org/find-duplicates-in-on-time-and-constant-extra-space

// Solution changing the input (cycle sort - problem very similar to that from Pramp/Exponent (__get_different_number_cycle_sort) - difference is that here nums are bounded in the interval [1, n]).
// O(N) in time and O(1) in space.
int findDuplicate(vector<int>& nums) {
	for (int i = 0; i < nums.size(); ++i) {
		while (nums[i] != i) {
			if (nums[nums[i]] == nums[i]) {
				return nums[i];
			}
			swap(nums[i], nums[nums[i]]);
		}
	}

	return -1;
}

// Clever idea for using binary search adaptation here (nice read-only over the input): find the smallest number such that the count of numbers less than or equal to it is greater than the number itself.
// 		log(N) times it goes through the entire array to get the count above = N log (N) solution.
int findDuplicateBinarySearch(vector<int>& nums) {
	// Lambda function to count how many numbers are less than or equal to 'cur'
	auto small_or_equal = [&](int cur) {
		int count = 0;
		for (auto &num: nums) {
			if (num <= cur)
				count++;
		}
		return count;
	};
	
	// 'low' and 'high' represent the range of values of the target
	int low = 1, high = nums.size(); // low = 0 also works, remember that small_or_equal goes through the entire vector anyway.
	int duplicate = -1;
	while (low <= high) {
		int cur = low + (high-low)/2;
		
		if (small_or_equal(cur) > cur) { 
			duplicate = cur;
			high = cur - 1;
		} else {
			low = cur + 1;
		}
	}

	return duplicate;
}

// The other solution below is O(sqrt(n)) in space and linear in time - nice idea too (read-only over input).
// Idea: define intervals of size sqrt(n) and use counting sort to find which interval contains the excess, after that do a final pass holding a hash set "seen" with size at most sqrt(n).
// Using sqrt for the size "l" of the intervals is a genius trick because it limitates 
// both the sizes of the vector "intervalsCount" (O(n/l)) and the set "s" later (O(l))
// ("l" and "n/l" will be both O(sqrt(n)) - final complexity in space :D )
// Ans: O(sqrt(n)) in memory and only 2 sequential passes through the stream.
int repeatedNumber(const vector<int> &A) {
	int n = A.size()-1;

	// Original way: using sqrt
	int l = ceil(sqrt((double) n)); //  interval size
	int nBuckets = ceil( ((double) n) / l );
	int m = n % l;

    // Trying to use log n in space (does not work - size of the set "s" below is not limited)
	// int nBuckets = floor(log((double) n));
	// nBuckets = nBuckets == 0 ? 1 : nBuckets;
	// int l = n / nBuckets; // interval size
	// int m = l;
	// if(n % nBuckets != 0) {
	// 	m = n % nBuckets;
	// 	nBuckets++;
	// }
	
	// cout << "l: " << l << endl;
	// cout << "nBuckets: " << nBuckets << endl;
	// cout << "m: " << m << endl;

	vector<int> intervalsCount (nBuckets, 0); // O(sqrt(n)) in space

	for(int el : A) {
		++intervalsCount[(el-1)/l];
	} 

	int indexInterval = 0;
	for(; indexInterval < nBuckets; indexInterval++) {
		int count = intervalsCount[indexInterval];
		if(count > l || (indexInterval == nBuckets-1 && count > m)) {
			break;
		}
	}
	int intervalDown = indexInterval*l+1;
	int intervalUp = (indexInterval+1)*l;

	// cout << "intervalDown: " << intervalDown << endl;
	// cout << "intervalUp: " << intervalUp << endl;
	
	// cout << "vector intervalsCount: ";
	// printVector(intervalsCount);

	unordered_set<int> s = {}; // O(sqrt(n)) in space

	for(int el : A) {
		if(el < intervalDown || el > intervalUp) {
			continue;
		}
		if(s.find(el) != s.end()) {
			return el;
		}
		s.insert(el);
	}

	// cout << "s.size(): " << s.size() << endl;

	return -1;
}


// Bit solution below (counting bits in [from 1 to n] and in nums and comparing) - O(N log N) in time, O(1) in space.
// Algorithm:
// 1. Initialize the answer (duplicat) to 0
// 2. Iterate over each bit from 0 to bits where bits is the bit-length of n.
// 		For each bit, iterate over every number from 1 through n and count how many times the bit is set to 1. This will be the base count (base_count).
// 		For each bit, iterate over every number in input array and count how many times the bit is set to 1. This will be the current count (nums_count).
// 		If nums_count > base_count, then set the current bit to 1 in duplicate
// 3. After checking each bit to see if it should be set in duplicate, and setting the bits with nums_count>base_count to 1, return the duplicate number.

// Find the position of the Most Significant Bit in num
int calcMaxBit(int num) {
	int bits = 0;
	while (num > 0) {
		num /= 2;
		bits++;
	}
	return bits;
}

int findDuplicateUsingBits(vector<int>& nums) {
	int duplicate = 0;
	int n = nums.size() - 1;
	int max_num = *max(nums.begin(), nums.end());
	int max_bit = calcMaxBit(max_num);
	
	// Iterate over each bit
	for (int bit = 0; bit < max_bit; bit++) {
		int mask = (1 << bit);
		int base_count = 0, nums_count = 0;
		
		for (int i = 0; i <= n; i++) {
			// If bit is set in number (i) then add 1 to base_count
			if (i & mask) {
				base_count++;
			}
			// If bit is set in nums[i] then add 1 to nums_count
			if (nums[i] & mask) {
				nums_count++;
			}
		}
		
		// If the current bit is more frequently set in nums than it is in 
		// the range [1, 2, ..., n] then it must also be set in the duplicate number
		if (nums_count > base_count) {
			duplicate |= mask;
		}
	}
	return duplicate;
}

int main() {
	cout << "Hello, World!";
	return 0;
}