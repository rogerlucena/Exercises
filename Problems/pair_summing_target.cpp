#include <iostream>
#include <vector>

using namespace std;

/*

 -- Problem statement:

 Find the two numbers in a sorted vector whose sum is equal to a target value.

*/

pair<int, int> FindPairSummingToTarget(const vector<int>& nums, int target) {
    int index1 = 0;
    int index2 = nums.size() - 1;

    pair<int, int> p(-1, -1);

    while (index1 < index2) {
        int sum = nums[index1] + nums[index2];
        if (sum < target) {
            index1++;
        } else if (sum > target) {
            index2--;
        } else {
            p = {index1, index2};
            break;
        }
    }

    return p;
}

int main() {
    vector<int> nums = {1, 2, 3, 5, 10, 23, 44, 137};
    int target = 13;

    pair<int, int> p = FindPairSummingToTarget(nums, target); // expected answer: (2, 4)
    cout << "The indexes of the numbers are: " << p.first << " " << p.second << endl;

    return 0;
}
