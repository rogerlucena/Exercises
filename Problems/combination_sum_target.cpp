#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_set>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/combination-sum-ii/

// Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

// Each number in C may only be used once in the combination.

// Note:
// All numbers (including target) will be positive integers.
// Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
// The solution set must not contain duplicate combinations.

// Example :
// Given candidate set 10,1,2,7,6,1,5 and target 8,
// A solution set is:
// [1, 7]
// [1, 2, 5]
// [2, 6]
// [1, 1, 6]

string vecToS(vector<int> &v) {
	string s = "";
	for(int el : v) {
		string elString = to_string(el);
		for(char c : elString) {
			s.push_back(c);
		}
		s.push_back(',');
	}
	return s;
}

// Instead of "ansHashes" you could also use a hash map with the number of occurences of every element in A;
// this way, we only add "currVector" to "ans" if used[A[i]] > 0, and then we decrement it
void auxCombinationSum(vector<int> &A, int target, int index, vector<int> currVector, vector<vector<int>> &ans, unordered_set<int> &ansHashes) {
	if(index >= A.size()) {
		return;
	}

	auxCombinationSum(A, target, index+1, currVector, ans, ansHashes);

	bool repeatedSolution = index > 0 ? A[index] == A[index-1] : false;
	currVector.push_back(A[index]);
	target -= A[index];
	if(target == 0) {
		int ansHash = hash<string>()(vecToS(currVector));
		if(ansHashes.find(ansHash) == ansHashes.end()) {
			ans.push_back(currVector);
			ansHashes.insert(ansHash);
		}
	}

	auxCombinationSum(A, target, index+1, currVector, ans, ansHashes);
}

vector<vector<int>> combinationSum(vector<int> &A, int B) {
    sort(A.begin(), A.end());
	vector<vector<int>> ans;
	unordered_set<int> ansHashes;
	auxCombinationSum(A, B, 0, {}, ans, ansHashes);

	return ans;
}


int main() {
	vector<int> A = {10,1,2,7,6,1,5};
	int B = 8;

	cout << "Answer:" << endl;
	
	for(vector<int> ans : combinationSum(A, B)) {
		printVector(ans);
	}

	return 0;
}