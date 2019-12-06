#include <iostream>
#include <vector>

using namespace std;

int main() {
	cout << "Hello, World!";
	return 0;
}

/*
vector<int> order(vector<int> &A, vector<int> &B) {
	if(A.empty()) {
		return vector<int>();
	}

	vector<pair<int, int>> heightsAndInfronts;
	for(int i = 0; i < A.size(); ++i) {
		heightsAndInfronts.push_back({A[i], B[i]});
	}

	// auto cmp = [](const pair<int, int> &p, const pair<int, int> &q) {return p.first < q.first;};
	sort(heightsAndInfronts.begin(), heightsAndInfronts.end()); // , cmp);

	// unordered_map<int, int> heightToPos;
	vector<int> ans(A.size(), -1);
	// unordered_set<int> usedPos;
	for(int i = 0; i < heightsAndInfronts.size(); ++i) {
		int h = heightsAndInfronts[i].first;
		int infronts = heightsAndInfronts[i].second;
		if(i == 0) {
			// heightToPos[h] = infronts;
			// usedPos.insert(infronts);
			ans[infronts] = h;
		} else {
			int j = 0;
			while(ans[j] != -1) {
				++j;
			}
			while(infronts > 0) {
				--infronts;
				++j;
				while(ans[j] != -1) {
					++j;
				}
			}
			// heightToPos[h] = j;
			// usedPos.insert(j);
			ans[j] = h;
		}
	}

	
	// for(pair<int, int> heightAndPos : heightToPos) {
	// 	ans[heightAndPos.second] = heightAndPos.first;
	// }

	return ans;
}

int main() {
	vector<int> heights = {5, 3, 2, 6, 1, 4};
	vector<int> infronts = {0, 1, 2, 0, 3, 2};

	printVector(order(heights, infronts));

	return 0;
}

*/