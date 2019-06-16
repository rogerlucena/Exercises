#include <iostream>

#include <algorithm> 
#include <vector>

using namespace std;

// Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). 
// n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which 
// together with x-axis forms a container, such that the container contains the most water.
// Note: You may not slant the container and n is at least 2.

// Example:
// Input: [1,8,6,2,5,4,8,3,7]
// Output: 49

// https://leetcode.com/problems/container-with-most-water/submissions/

int maxArea(vector<int>& height) {
  int s = 0;
  int e = height.size()-1;
  int maxv = 0;
  int maxh = 0;
  for(int h : height) {
    if(h > maxh) {
      maxh = h;
    }
  }
  while(s < e) {
    if((e-s)*maxh < maxv) {
      break;
    }
    int currv = (e-s)*min(height[s], height[e]);
    if(currv > maxv) {
      maxv = currv;
    }
    if(height[s] < height[e]) {
      ++s;
    } else {
      --e;
    }
  }
  
  return maxv;        
}

int maxAreaSlow(vector<int>& height) {
  int s = height.size();
  int maxv = 0;
  for(int i=0; i<s; i++) {
    if(height[i]*(s-1) < maxv) {
      continue;
    }
    for(int j=i+1; j<s; j++) {
      int currv = (j-i)*min(height[i], height[j]);
      if(currv > maxv) {
        maxv = currv;
      }
    }
  }

  return maxv;        
}

int main() {
    vector<int> h = {1,8,6,2,5,4,8,3,7};

    cout << "maxArea: " << maxArea(h) << endl;
    cout << "End of Program.";
    return 0;
}