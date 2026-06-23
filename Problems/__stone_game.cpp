#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// https://neetcode.io/problems/stone-game
// https://leetcode.com/problems/stone-game
// Remember: see recursion with repeatead subcases -> need for memoization -> nice 2D DP with min-max in a game.

// Alice and Bob are playing a game with piles of stones. There are an even number of piles arranged in a 
// row, and each pile has a positive integer number of stones piles[i].

// The objective of the game is to end with the most stones. The total number of stones across all the piles 
// is odd, so there are no ties.

// Alice and Bob take turns, with Alice starting first. Each turn, a player takes the entire pile of stones 
// either from the beginning or from the end of the row. This continues until there are no more piles left, at which point the person with the most stones wins.

// Assuming Alice and Bob play optimally, return true if Alice wins the game, or false if Bob wins.

// Example:
// Input: piles = [1,2,3,1]
// Output: true

// O(N^2) in time and space.
int getAliceScore(const vector<int>& piles, int l, int r, vector<vector<int>>& memo) {
    if (l > r) {
        return 0;
    }

    if (memo[l][r] != -1) {
        return memo[l][r];
    }

    if ((r - l + 1) % 2 == 1) {  // Bob's turn.
        memo[l][r] = min(getAliceScore(piles, l + 1, r, memo), getAliceScore(piles, l, r - 1, memo));
    } else {
        memo[l][r] = max(piles[l] + getAliceScore(piles, l + 1, r, memo), piles[r] + getAliceScore(piles, l, r - 1, memo));
    }

    return memo[l][r];
}

bool stoneGame(vector<int>& piles) {
    int n_piles = piles.size();
    int total_stones = accumulate(piles.begin(), piles.end(), 0);

    vector<vector<int>> memo(n_piles, vector<int>(n_piles, -1));
    int alice_score = getAliceScore(piles, 0, n_piles - 1, memo);
    
    return alice_score > (total_stones - alice_score);
}

// Another idea is to use the "margin" concept (current pile minus max future) - this way there is no need to differentiate Alice's turn from Bob's.
class Solution {
public:
    int getOptimalMargin(int i, int j, const vector<int>& piles, vector<vector<int>>& memo) {
        // Base case: no piles left
        if (i > j) return 0;
        
        // Return already calculated state
        if (memo[i][j] != -1) return memo[i][j];

        // Choose the option that maximizes current player's margin over opponent
        int pickLeft = piles[i] - getOptimalMargin(i + 1, j, piles, memo);
        int pickRight = piles[j] - getOptimalMargin(i, j - 1, piles, memo);

        return memo[i][j] = max(pickLeft, pickRight);
    }

    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        
        // If Alice's final relative margin over Bob is greater than 0, Alice wins.
        return getOptimalMargin(0, n - 1, piles, memo) > 0;
    }
};

int main() {
	cout << "Hello, World!";
	return 0;
}