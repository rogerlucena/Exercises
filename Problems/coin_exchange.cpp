#include <iostream>
#include <vector>
#include <limits.h>
#include <unordered_map>
using namespace std;

/*

-- Problem statement:

- Coin exchange:

You are given the currency coin values [v1,v2,...] sorted in ascending order and
a target value. You wanna output the minimum number of coins needed to result the
target.

INPUT: vector<int> coins, int target
OUTPUT: int minimum amount of coins.

Follow up: give an example where a greedy approach works and another where it doesn't.

*/

// Solution: using Dynamic Programming (recursive solution, with memoization)

int minNumber(vector<int> coins, int target, int ncoins, unordered_map<int, int> &tableValueMinimun) {
    if(target<0)
        return INT_MAX;
    if(target == 0) {
        return ncoins;
    }
    else{
        unordered_map<int, int>::const_iterator got = tableValueMinimun.find(target);
        if(got != tableValueMinimun.end())
            return got->second;
        else{
            int val = min(minNumber(coins, target-2, ncoins+1, tableValueMinimun), min(minNumber(coins, target-5, ncoins+1, tableValueMinimun), minNumber(coins, target-10, ncoins+1, tableValueMinimun)));
            tableValueMinimun[target] = val;
            return val;
        }
    }
}

int main()
{
    // Setting the problem's parameters:
    vector<int> coins = {2, 5, 10};
    int target = 15;

    // Memoization:
    unordered_map<int, int> tableValueMinimun;

    int minCoins = minNumber(coins, target, 0, tableValueMinimun);
    if(minCoins == INT_MAX)
        cout << "There is no way of getting this target value using the current coins." << endl;
    else
        cout << "The minimun number of coins is: " << minCoins << endl;
    return 0;
}

// P.S.:
// Always good to know:
// INT_MAX = (2^32)/2 - 1 = 2.147.483.647 (32 bits used - signed int, from limits.h)