#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*

 Given an array, find the indexes of the 2 numbers summing to a target (they always exist!):

 https://leetcode.com/problems/two-sum/description/

*/

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
      vector<int> sol(2, 0);
      vector<int> nums2(nums);

      sort(nums2.begin(), nums2.end());
      int i=0;
      int f=nums2.size()-1;

      while(i<f) {
          //cout << "i: " << i << " f: " << f << endl;
          if(nums2[i]+nums2[f]==target) break;
          else if(nums2[i]+nums2[f]>target) --f;
          else ++i;
      }

      if(i>=f) throw "Error!!"; // must have one unique solution

      for(int idx=0; idx<nums.size(); ++idx) {
          if(nums[idx] == nums2[i]) {
              sol[0] = idx;
              break;
          }
      }
      for(int idx=0; idx<nums.size(); ++idx) {
          if(idx != sol[0] && nums[idx] == nums2[f]) {
              sol[1] = idx;
              break;
          }
      }


      return sol;
  }
};

int main()
{
    vector<int> vec = {-1,-2,-3,-4,-5};
    int target = -8;

    Solution sol;
    auto resp = sol.twoSum(vec, target);

    cout << vec[resp[0]] << " and " << vec[resp[1]] << " must sum: " << target << endl;

    return 0;
}