#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/max-distance/

// Given an array A of integers, find the maximum of j - i subjected to the constraint of A[i] <= A[j].

// Example:
// A : [3 5 4 2]
// Output : 2 
// for the pair (3, 4)

// genius trick: after sorting and keeping the original indexes for every new A[i] in indexes[i],
//   		     do a preprocessing over indexes to generate a new array called indexMax with the 
//               max index taken from indexes of every element to the right of indexes[i]
//               Think BACKWARDS on the vector to the pre-processing be O(n)! (accumulate information thinking)

auto printEl = [](const pair<int, int> &p) -> void {std::cout << "(" << p.first << "," << p.second << ")";};

// O(n), very useful pre-processing
// Could also "generate this vector on the fly inside the last loop of "maximumGap", doing the loop backwardss
vector<int> getIndexMaxVector(const vector<pair<int, int>> &newA) {
	vector<int> indexMax(newA.size());
	int currIndexMax = INT_MIN;

	for(int i = newA.size()-1; i >=0; --i) {
		currIndexMax = max(currIndexMax, newA[i].second);
		indexMax[i] = currIndexMax;
	}

	return indexMax;
}

int maximumGap(const vector<int> &A) {
	if(A.size() == 0) {
		return -1;
	}

	vector<pair<int, int>> newA; // vector with pairs (element of original A, original position in A)
	newA.reserve(A.size());

	for(int i = 0; i < A.size(); ++i) {
		pair<int, int> p = {A[i], i};
		newA.push_back(p);	
	}
	
	// auto smaller = [](const pair<int, int> &p1, const pair<int, int> &p2) -> bool{return p1.first < p2.first;};
	sort(newA.begin(), newA.end()); // for sort, default is taking .first do pair

	vector<int> indexMax = getIndexMaxVector(newA);

	int ans = 0;
	for(int i = 0; i < newA.size()-1; ++i) { // could also "generate" indexMax here, on the fly, like in maximumGapImproved
		pair<int, int> p = newA[i];
		ans = max(ans, indexMax[i+1] - p.second);
	}

	// printVector(newA, (std::function<void(const pair<int, int>&)>) printEl);
	return ans;
}

// Best solution, in-place:
int maximumGapImproved(const vector<int> &A) {
	if(A.size() == 0) {
		return -1;
	}

	vector<pair<int, int>> newA; 
	newA.reserve(A.size());

	for(int i = 0; i < A.size(); ++i) {
		pair<int, int> p = {A[i], i};
		newA.push_back(p);	
	}
	
	sort(newA.begin(), newA.end()); 

	int ans = 0;
	int currIndexMax = newA[newA.size()-1].second; 
	for(int i = newA.size()-2; i >= 0; --i) { 
		pair<int, int> p = newA[i];
		ans = max(ans, currIndexMax - p.second);
		currIndexMax = max(currIndexMax, p.second); // generating vector "indexMax" on the fly
	}

	return ans;
}

int main() {
	vector<int> A = {3, 5, 4, 2};
	std::cout << "maximumGap: " << maximumGapImproved(A) << endl;

	return 0;
}