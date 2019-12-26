#include <iostream>
#include <vector>

using namespace std;

// https://www.pramp.com/challenge/jKoA5GAVy9Sr9jGBjz04
// Adaptation of binary search. Use ALL the information! Use > and < too.

// Given a sorted array arr of distinct integers, write a function indexEqualsValueSearch 
// that returns the lowest index i for which arr[i] == i. Return -1 if there is no such index. 

// if arr[mid] > mid, you can already eliminate the right side
int indexEqualsValueSearch(const vector<int> &arr) {
  // your code goes here
  int l = 0;
  int r = arr.size()-1;
  
  int ans = -1;
  
  while(l <= r) {
    int mid = (l+r)/2;
    if(arr[mid] == mid) {
      ans = mid;
      r = mid -1;
    } 
    
    else if(arr[mid] > mid) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  
  return ans;
}

int main() {
	vector<int> arr = {-8, 0, 2, 5};
	cout << "Answer: " << indexEqualsValueSearch(arr) << endl;

	return 0;
}