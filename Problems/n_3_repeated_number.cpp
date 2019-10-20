#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int repeatedNumber(const vector<int> &A) {
	unordered_map<int, int> m;

	for(int e : A) {
		if(m.find(e) != m.end()) {
			// cout << "Incrementing: " << e << " to " << m[e]+1 << endl;
			m[e] = m[e]+1;
		} else if(m.size() < 2) {
			m[e] = 1;
		} else {
			vector<unordered_map<int, int>::iterator> toDelete;
			for(unordered_map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
				it->second = it->second-1;
				if(it->second == 0) {
					toDelete.push_back(it);
				}
			}
			for(unordered_map<int, int>::iterator it : toDelete) {
				// cout << "Erasing: " << it->first << endl;
				m.erase(it);
			}
		}
	}

	for(pair<int, int> p : m) {
		// cout << "p.second: " << p.second << endl;
		int count = 0;
		for(int e : A) {
			if(e == p.first) {
				++count;
			}
		}
		if(count > A.size()/3) {
			return p.first;
		}
	}

	return -1;
}

int main() {
	vector<int> A = {1, 2, 3, 1, 1};
	// vector<int> A = {1, 1, 1, 2, 3, 5, 7};

	cout << "Answer:" << endl << repeatedNumber(A) << endl;
	return 0;
}