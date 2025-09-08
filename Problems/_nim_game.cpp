#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/nim-game
// Remember: test by hand the first cases and you will see the pattern.
// DP here gives memory limit exceeds.

// You are playing the following Nim Game with your friend:

// Initially, there is a heap of stones on the table.
// You and your friend will alternate taking turns, and you go first.
// On each turn, the person whose turn it is will remove 1 to 3 stones from the heap.
// The one who removes the last stone is the winner.
// Given n, the number of stones in the heap, return true if you can win the game assuming both you 
// and your friend play optimally, otherwise return false.

// Example:
// Input: n = 4
// Output: false
// Explanation: These are the possible outcomes:
// 1. You remove 1 stone. Your friend removes 3 stones, including the last stone. Your friend wins.
// 2. You remove 2 stones. Your friend removes 2 stones, including the last stone. Your friend wins.
// 3. You remove 3 stones. Your friend removes the last stone. Your friend wins.
// In all outcomes, your friend wins.

bool canWinNim(int n) {
    return n % 4 != 0;
}

int main() {
	cout << "Hello, World!";
	return 0;
}