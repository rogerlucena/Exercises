#include <iostream>
#include <vector>
#include <map>

using namespace std;

// https://www.interviewbit.com/problems/inversions/

// Given an array A, count the number of inversions in the array.

// Formally speaking, two elements A[i] and A[j] form an inversion if A[i] > A[j] and i < j

// Example:
// A : [2, 4, 1, 3, 5]
// Output : 3
// as the 3 inversions are (2, 1), (4, 1), (4, 3).

// Website solution:
long long rec(vector<int> &v, int l, int r) {
    if(l >= r) {
		return 0;
	}

    int m = (l + r) / 2;
    long long count = rec(v, l, m);
    count += rec(v, m + 1, r);
    
	// Below it is sorting "v" in the interval [l, r] so the algorithm works with (*),
	// while counting the inversions, like a enhanced merge sort https://www.geeksforgeeks.org/counting-inversions/
    vector<int> aux(v.begin() + l, v.begin() + m + 1);
    int i = m + 1;
	int j = 0; // index in aux
    for(int k = l; k <= r; k++) {
        if(j == aux.size() || (i <= r && v[i] < aux[j])) {
            count += (aux.size() - j); // (*)
            v[k] = v[i++];
        } else {
            v[k] = aux[j++];
		}
    }

    return count;
}

int countInversions(vector<int> &A) {
    return rec(A, 0, int(A.size()) - 1);
}

// Old solution below, O(n^2) in the worst case
int oldCountInversions(vector<int> &A) {
	map<int, int> m;

	for(int i : A) { // O(n log n)
		if(m.find(i) != m.end()) {
			m[i] += 1;
		} else {
			m[i] = 1;
		}
	}

	int invertions = 0;
	for(int i : A) {
		if(m[i] > 1) { // O(log n)
			m[i] -= 1;
		} else {
			m.erase(i);  // O(log n)
		}
		
		for(map<int, int>::iterator it = m.begin(); it != m.end(); ++it) { // linear in the worst case
			if(i == it->first) {
				continue;
			} else if(i > it->first) {
				invertions += it->second;
			} else {
				break;
			}
		}
	}
	
	return invertions;
}


int main() {
	vector<int> A = {7, 3, 1, 1};
	cout << "Answer: " << countInversions(A) << endl;

	return 0;
}