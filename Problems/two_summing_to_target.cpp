#include <iostream>
#include <vector>
#include <unordered_map>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/2-sum/

// Given an array of integers, find two numbers such that they add up to a specific target number.

// The function twoSum should return indices of the two numbers such that they add up to the target, where index1 < index2. Please note that your returned answers (both index1 and index2 ) are not zero-based.
// Put both these numbers in order in an array and return the array from your function ( Looking at the function signature will make things clearer ). Note that, if no pair exists, return empty list.

// If multiple solutions exist, output the one where index2 is minimum. If there are multiple solutions with the minimum index2, choose the one with minimum index1 out of them.

// Example:
// Input: [2, 7, 11, 15], target=9
// Output: index1 = 1, index2 = 2

// Website solution, elegant:
vector<int> twoSum(const vector<int> &A, int B) {
	unordered_map<int, int> M;
	vector<int> ans;

	for (int i = 0; i < A.size(); i++) {
		int required = B - A[i];
		if (M.find(required) != M.end()) {
			// We have our solution. index1 = M[required], index2 = i + 1 ( 1 based ). 
			ans.push_back(M[required]);
			ans.push_back(i + 1);
			return ans;
		}
		if (M.find(A[i]) == M.end()) {
			// We want to maintain the minimum index at M[A[i]]. i + 1 will 
			// obviously be greater than whats already present.
			M[A[i]] = i + 1;
		}
	}
	return ans;
}

vector<int> oldTwoSum(const vector<int> &A, int B) {
	vector<int> ans = {};
	unordered_map<int, int> m = {};
	for(int i = A.size()-1; i >= 0; --i) {
		m[A[i]] = i;
	}

	for(int i = A.size()-1; i >= 0; --i) {
		unordered_map<int, int>::iterator got = m.find(B-A[i]);
		if(got != m.end() && got->second < i) {
			int index2 = i;
			int index1 = got->second;
			if(ans.empty()) {
				ans.push_back(index1);
				ans.push_back(index2);
			} else {
				if(index2 < ans[1] || (index2 == ans[1] && index1 < ans[0])) {
					ans[0] = index1;
					ans[1] = index2;
				}
			}
		}
	}

	if(!ans.empty()) {
		ans[0] += 1;
		ans[1] += 1;
	}
	return ans;
}

int main() {
	vector<int> A = {2, 7, 11, 15};
	int B = 9;
	cout << "Answer:" << endl;
	printVector(twoSum(A, B));

	return 0;
}