#include <iostream>
#include <vector>
#include <map>

using namespace std;

// https://www.interviewbit.com/problems/distribute-candy/

// There are N children standing in a line. Each child is assigned a rating value.

// You are giving candies to these children subjected to the following requirements:

// 1. Each child must have at least one candy.
// 2. Children with a higher rating get more candies than their neighbors.
// What is the minimum candies you must give?

// Input Format:
// The first and the only argument contains N integers in an array A.
// Output Format:
// Return an integer, representing the minimum candies to be given.

// Example:
// Input 1:
//     A = [1, 2]

// Output 1:
//     3
// Explanation 1:
//     The candidate with 1 rating gets 1 candy and candidate with rating cannot get 1 candy as 1 is its neighbor. 
//     So rating 2 candidate gets 2 candies. In total, 2 + 1 = 3 candies need to be given out.

// Input 2:
//     A = [1, 5, 2, 1]
// Output 2:
//     7
// Explanation 2:
//     Candies given = [1, 3, 2, 1]

bool compare(pair<int, int> a, pair<int, int> b) {
    if (a.second < b.second) {
        return true;
	}

    return false;
}

int candy(vector<int> &A) {
    vector<pair<int, int>> v;
    int n = A.size();
    for (int i = 0; i < n; i++) {
        v.push_back(make_pair(i, A[i]));
	}
    sort(v.begin(), v.end(), compare);

    vector<int> distribution(n, 0);

    for (int i = 0; i < n; i++) {
        int pos = v[i].first;
        int rating = v[i].second;
        if (pos - 1 < 0) {
            if (A[pos + 1] > rating) distribution[pos] = 1;
            else if (A[pos + 1] < rating) distribution[pos] = distribution[pos + 1] + 1;
            else distribution[pos] = 1;
        }
        else if (pos + 1 >= n) {
            if (A[pos - 1] > rating) distribution[pos] = 1;
            else if (A[pos - 1] < rating) distribution[pos] = distribution[pos - 1] + 1;
            else distribution[pos] = 1;
        }
        else {
            int candy = 1;
            if (A[pos - 1] < rating) candy = max(candy, distribution[pos - 1]+1);
            if (A[pos + 1] < rating) candy = max(candy, distribution[pos + 1]+1);
            distribution[pos] = candy;
        }
    }

    int candies_count = 0;
    for (int i = 0; i < n; i++) {
        candies_count += distribution[i];
    }

    return candies_count;
}

int main() {
	vector<int> A = {1, 5, 2, 1};
	cout << "Answer: " << candy(A) << endl;

	return 0;
}