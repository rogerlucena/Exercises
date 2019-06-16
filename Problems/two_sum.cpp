#include <iostream>

#include <unordered_set>
#include <unordered_map>
#include <vector>

// Problem:
// For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.
// https://leetcode.com/problems/two-sum/

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
  vector<int> ans = {};
  unordered_map<int, int> elindex = {};
  for(int i = 0; i < nums.size(); i++) {
    int el = nums[i];
    int diff = target-el;
    if(elindex.find(diff) != elindex.end()) {
      ans.push_back(elindex[diff]);
      ans.push_back(i);
      return ans;
    }
    elindex[el] = i;
  }
  return ans;  
}

int main() {
  // Setting the problem's parameters:
  vector<int> arr = {10, 15, 3, 8, 2};
  int k = 17;

  unordered_set<int> possiblemysetcomplements = {};

  bool ans = false;
  for(int el : arr) {
    if(possiblemysetcomplements.find(el) != possiblemysetcomplements.end()) {
      ans = true;
      break;
    }
    possiblemysetcomplements.insert(k-el);
    cout << "possiblemysetcomplements: " << *possiblemysetcomplements.begin() << " size: " << possiblemysetcomplements.size() << endl;
  }

  cout << "Answer: " << ans << endl;
  if(ans) {
    vector<int> p = twoSum(arr, k);
    cout << "(" << p[0] << ", " << p[1] << ")" << endl;
  }

  return 0;
}