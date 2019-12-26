#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// https://www.pramp.com/challenge/XdMZJgZoAnFXqwjJwnpZ

// Pairs with Specific Difference
// Given an array arr of distinct integers and a nonnegative integer k, write a function 
// findPairsWithGivenDifference that returns an array of all pairs [x,y] in arr, such that x - y = k. 
// If no such pairs exist, return an empty array.

// Note: the order of the pairs in the output array should maintain the order of the y element in the 
// original array.

// Examples:

// input:  arr = [0, -1, -2, 2, 1], k = 1
// output: [[1, 0], [0, -1], [-1, -2], [2, 1]]

// input:  arr = [1, 7, 5, 3, 32, 17, 12], k = 17
// output: []

vector<vector<int>> findPairsWithGivenDifference(const vector<int> &arr, int k) {
  vector<vector<int>> ans;
  if(k == 0) {
    return ans;
  }
  
  unordered_set<int> s;
  for(int el : arr) {
    s.insert(el);
  }
  
  for(int y : arr) {
    int x = y + k;
    if(s.find(x) != s.end()) {
      ans.push_back({x, y});
    }
  }
  
  return ans;
}

int main() {
	cout << "Hello, World!";
	return 0;
}