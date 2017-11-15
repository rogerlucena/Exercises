#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

/*

-- Problem: k sorted vectors are given, merge them in one sorted vector

*/

// My solution: O(n log k) in time
// Using priority queue to make the comparisons between the
// k elements (one from each vector) faster

class CompareDist
{
 public:
    bool operator()(pair<int,int> n1,pair<int,int> n2) {
        return n1.second>n2.second;
    }
};

// make_pair(currK, vectors[currK][++indexes[currK]])
pair<int, int> getNextPair(const int &k, int &currK, const vector<vector<int>> &vectors, vector<int> &indexes) {
    ++indexes[currK];

    if(indexes[currK] < vectors[currK].size()){
        return make_pair(currK, vectors[currK][indexes[currK]]);
    }
    else{
        currK=(currK+1)%k;
        for(++indexes[currK]; indexes[currK]>=vectors[currK].size();) {
            ++indexes[currK];
            currK=(currK+1)%k;
        }
        return make_pair(currK, vectors[currK][indexes[currK]]);
    }
}

vector<int> mergeVectors(vector<vector<int>> vectors) {
    vector<int> sol;
    int k = vectors.size();

    vector<int> indexes(k, 0);

    // Computing the total number of elements "n"
    int n = 0;
    for(vector<int> v : vectors) {
        n += v.size();
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareDist> pq;
    for(int ki=0; ki < k; ++ki) {
        pair<int, int> p (ki, vectors[ki][indexes[ki]]);
        pq.push(p);
    }


    while(n > 0) {
        pair<int, int> p = pq.top();
        int top = p.second;
        int currK = p.first;
        pq.pop();

        if(n > k) pq.push(getNextPair(k, currK, vectors, indexes));
        sol.push_back(top);

        --n;
    }

    return sol;
}

int main()
{
    vector<int> v1 = {1, 3, 5, 6, 10};
    vector<int> v2 = {2, 7, 8};
    vector<int> v3 = {4, 9};

    vector<vector<int>> vectors = {v1, v2, v3};

    vector<int> sol = mergeVectors(vectors);

    for(int i : sol) {
        cout << i << " ";
    }

    return 0;
}