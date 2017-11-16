#include <iostream>
#include <vector>

using namespace std;

/*

 -- Problem statement: https://www.hackerrank.com/challenges/stockmax/problem
 (Dynamic Programming)

 Basically, with the stock action values for the next N days, find the maximum profit
 (operations: but one action, sell what you have or do nothing each day)

 // I still have to improve its performance, memoization should help for example.

 - Sample input:
 3
 3
 5 3 2
 3
 1 2 100
 4
 1 3 1 2

 - Sample output:
 0
 197
 3

*/

int auxGetMaxProfit(const vector<int> &v, int day, int profit, int currShares){
    if(day >= v.size()) return profit;

    int p1 = auxGetMaxProfit(v, day+1, profit, currShares);
    int p2 = auxGetMaxProfit(v, day+1, profit-v[day], currShares+1);
    int p3 = auxGetMaxProfit(v, day+1, profit+currShares*v[day], 0);

    return max(max(p1, p2), p3);
}

// Implement this method:
int getMaxProfit(vector<int> v) {
    int currShares = 0;
    int myProfit = 0;
    int p1 = auxGetMaxProfit(v, 1, myProfit, currShares);
    int p2 = auxGetMaxProfit(v, 1, myProfit-v[0], currShares+1);
    return max(p1, p2);
}

int main()
{
    int T; // number of tests
    cin >> T;
    for(int i=1; i<=T; ++i) {
        int N;
        cin >> N; // number of days
        vector<int> v;
        for(int i=1; i<=N; ++i){
            int n;
            cin >> n;
            v.push_back(n);
        }
        int maxProfit = getMaxProfit(v);
        cout << maxProfit << endl;
    }
    return 0;
}