#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>

using namespace std;

#define MOD 1000000007ll

// https://www.interviewbit.com/problems/different-bits-sum-pairwise/

// We define f(X, Y) as number of different corresponding bits in binary representation of X and Y. For example, f(2, 7) = 2, since binary representation of 2 and 7 are 010 and 111, respectively. The first and the third bit differ, so f(2, 7) = 2.
// You are given an array of N positive integers, A1, A2 ,…, AN. Find sum of f(Ai, Aj) for all pairs (i, j) such that 1 ≤ i, j ≤ N. Return the answer modulo 109+7.

// For example,
// A=[1, 3, 5]

// We return:

// f(1, 1) + f(1, 3) + f(1, 5) + 
// f(3, 1) + f(3, 3) + f(3, 5) +
// f(5, 1) + f(5, 3) + f(5, 5) =

// 0 + 1 + 1 +
// 1 + 0 + 2 +
// 1 + 2 + 0 = 8

int cntBits(vector<int> &A) {
	int ans = 0;
	for(int p = 0; p < 31; ++p) {
		long n0 = 0, n1 = 0; // number of bits 0 and 1 at the position being analyzed
		for(int i = 0; i < A.size(); ++i) {
			int a = A[i];
			if(((a >> p) & 1) == 0) {
				++n0;
			} else {
				++n1;
			}
		}
		ans += (2 * n0 * n1) % MOD;
		ans %= MOD;
	}

	return ans;
}

// Old way below
long f(int a, int b, unordered_map<string, long> &m) {
	string pair = to_string(a) + "," + to_string(b);
	if(m.find(pair) != m.end()) {
		return m[pair];
	}

	int aXorB = a ^ b;
	long count = 0;
	while(aXorB != 0) {
		++count;
		aXorB = aXorB & (aXorB-1);
	}

	m[pair] = count;
	return count;
}

int oldCntBits(vector<int> &A) {
	sort(A.begin(), A.end());
	long ans = 0;
	unordered_map<string, long> m;
	for(int i = 0; i < A.size(); ++i) {
		for(int p = i; p < A.size(); ++p) {
			if(p > i) {
				ans += 2 * f(A[i], A[p], m);
			} else {
				ans += f(A[i], A[p], m);
			}
		}
	}

	return (int) (ans % 1000000007);
}


int main() {
	vector<int> A = {1, 3, 5};
	cout << "Answer: " << cntBits(A) << endl;
	return 0;
}