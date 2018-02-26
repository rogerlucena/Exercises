#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

/*

 Given two vectors of int numbers, find the pair with the smallest non-negative difference,
 return this difference

 (Problem 16.6, pg 181 of Cracking the Coding Interview, 6th edition)

*/

int smallestDifference(vector<int> &v1, vector<int> &v2) {
  int diff = INT_MAX;
  int i1, i2;
  i1 = i2 = 0;
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());

  while (i1 < v1.size() && i2 < v2.size()) {
    int d = abs(v1[i1] - v2[i2]);
    if (d < diff) {
      diff = d;
    }
    if (v1[i1] < v2[i2]) {
      ++i1;
    } else {
      ++i2;
    }
  }

  return diff;

}

int main()
{
  vector<int> v1 = {1, 3, 15, 11, 2};
  vector<int> v2 = {23, 127, 235, 19, 8};

  int res = smallestDifference(v1, v2);

  cout << "smallest difference: " << res << endl;

  return 0;
}