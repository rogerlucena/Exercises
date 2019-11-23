#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

#include "tools.cpp"

using namespace std;

// https://www.interviewbit.com/problems/get-mode-array-updates/?test_id=9944

// Get Mode Array Updates
// You are given an array of N positive integers, A1, A2 ,…, AN.
// Also, given a Q updates of form:

// i j: Update Ai = j. 1 ≤ i ≤ N.
// Perform all updates and after each such update report mode of the array. Therefore, return an 
// array of Q elements, where ith element is mode of the array after ith update has been executed.

// Notes

// Mode is the most frequently occuring element on the array.
// If multiple modes are possible, return the smallest one.
// Update array input is via a Q*2 array, where each row represents a update.
// For example,

// A=[2, 2, 2, 3, 3]

// Updates=    [ [1, 3] ]
//             [ [5, 4] ]
//             [ [2, 4] ]

// A = [3, 2, 2, 3, 3] after 1st update.
// 3 is mode.

// A = [3, 2, 2, 3, 4] after 2nd update.
// 2 and 3 both are mode. Return smaller i.e. 2.

// A = [3, 4, 2, 3, 4] after 3rd update.
// 3 and 4 both are mode. Return smaller i.e. 3.

// Return array [3, 2, 3].
// Constraints
// 1 ≤ N, Q ≤ 105
// 1 ≤ j, Ai ≤ 109


bool cmp(const pair<int, int> &p1, const pair<int, int> &p2) {
	if(p1.second != p2.second) {
		return p1.second > p2.second;
	}

	return p1.first <= p2.first;
}

// bool cmp(int a, int b) {
// 	return a > b;
// }

void decreaseIncreaseOcc(int dec, int inc, 
						 set<pair<int, int>, bool(*)(const pair<int, int>&, const pair<int, int>&)> &occ, 
						 unordered_map<int, pair<int, int>*> &elPointer) {
	pair<int, int>* pdec = elPointer[dec];
	if(pdec->second == 1) {
		occ.erase(*pdec);
		elPointer.erase(dec);
	} else {
		pair<int, int> newdec = make_pair(dec, pdec->second-1);
		occ.erase(*pdec);
		occ.insert(newdec);
		elPointer[dec] = &newdec;
	}
	// delete pdec;
	

	if(elPointer.find(inc) != elPointer.end()) {
		pair<int, int>* pinc = elPointer[inc];
		pair<int, int> newinc = make_pair(inc, pinc->second+1);
		occ.erase(*pinc);
		occ.insert(newinc);
		elPointer[inc] = &newinc;
		// delete pinc;
	} else {
		pair<int, int> newinc = make_pair(inc, 1);
		occ.insert(newinc);
		elPointer[inc] = &newinc;
	}
	// pair<int, int>* pinc = elPointer[inc];
	// if(pinc) {
	// 	++pinc->second;
}


// int getModeOcc(map<int, int, bool(*)(int, int)> &occ) {
// 	pair<int, int> ans = *occ.begin();
// 	for(pair<int, int> p : occ) {
// 		if(p.second == ans.second) {
// 			ans = p.first < ans.first ? p : ans;
// 		} else {
// 			break;
// 		}
// 	}	

// 	return ans.first;
// }

// ---
// void decreaseIncreaseOcc(int dec, int inc, unordered_map<int, int> &occ) {
// 	if(occ[dec] == 1) {
// 		occ.erase(dec);
// 	} else {
// 		--occ[dec];
// 	}

// 	if(occ.find(inc) != occ.end()) {
// 		++occ[inc];
// 	} else {
// 		occ[inc] = 1;
// 	}
// }

// int getModeOcc(unordered_map<int, int> &occ) {
// 	pair<int, int> ans = *occ.begin();
// 	for(pair<int, int> p : occ) {
// 		if(p.second == ans.second) {
// 			ans = p.first < ans.first ? p : ans;
// 		} else {
// 			ans = p.second > ans.second ? p : ans;
// 		}
// 	}	

// 	return ans.first;
// }

vector<int> getMode(vector<int> &A, vector<vector<int>> &B) {
	vector<int> ans;

  	// map<char,int,bool(*)(char,char)> fifth (fn_pt);
	// bool(*fn_pt)(const pair<int, int>&, const pair<int, int>&) = cmp;
	set<pair<int, int>, bool(*)(const pair<int, int>&, const pair<int, int>&)> occ(&cmp); 
	
	unordered_map<int, pair<int, int>*> elPointer; // // set<pair<int, int>, bool(*)(const pair<int, int>&, const pair<int, int>&)>::iterator
	for(int el : A) {
		if(elPointer.find(el) != elPointer.end()) {
			++elPointer[el]->second;
		} else {
			pair<int, int> p = make_pair(el, 1);
			elPointer[el] = &p;
		}
	}

	for(pair<int, pair<int, int>*> p : elPointer) {
		occ.insert(*p.second);
	}

	for(vector<int> up : B) {
		decreaseIncreaseOcc(A[up[0]-1], up[1], occ, elPointer);
		A[up[0]-1] = up[1];
		int moda = occ.begin()->first; // getModeOcc(occ);
		ans.push_back(moda);
	}

	return ans;
}


int main() {
	vector<int> A = { 2, 2, 2, 3, 3 };
	vector<vector<int>> B = {
		{1, 3},
		{5, 4},
		{2, 4}
	}; // ans: 3 2 3 
	cout << "Answer:" << endl;
	printVector(getMode(A, B));

	return 0;
}