#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://www.pramp.com/challenge/r1Kw0vwG6OhK9AEGAyWV

// The awards committee of your alma mater (i.e. your college/university) asked for your assistance with a
// budget allocation problem they’re facing. Originally, the committee planned to give N research grants this year.
// However, due to spending cutbacks, the budget was reduced to newBudget dollars and now they need to reallocate the grants.
// The committee made a decision that they’d like to impact as few grant recipients as possible by applying a maximum cap on all grants.
// Every grant initially planned to be higher than cap will now be exactly cap dollars. Grants less or equal to cap, obviously, won’t be
// impacted.

// Given an array grantsArray of the original grants and the reduced budget newBudget, write a function findGrantsCap that finds in the
// most efficient manner a cap such that the least number of recipients is impacted and that the new budget constraint is met (i.e. sum
// of the N reallocated grants equals to newBudget).

// Analyze the time and space complexities of your solution.

// Example:

// input:  grantsArray = [2, 100, 50, 120, 1000], newBudget = 190

// output: 47 # and given this cap the new grants array would be
//            # [2, 47, 47, 47, 47]. Notice that the sum of the
//            # new grants is indeed 190

// Start with brute force, and only then optimize! 

// O(N log N) in time below, O(1) in space.
// Idea: think if sorted array can help - yes, so sort it and try to use that.
double findGrantsCap(vector<int> grantsArray, int newBudget) {
	sort(grantsArray.begin(), grantsArray.end());
	int n = grantsArray.size();
	double guess = (newBudget * 1.0) / n;

	for (int i = 0; i < n && guess > grantsArray[i]; ++i) {
		double wallet = guess - grantsArray[i];
		guess += wallet / (n - i - 1);
	}

	return guess;
}

/*
[2, 100, 50, 120, 1000]  newBudget = 190
[2, 50, 100, 120, 1000] - sorted
[38, 38, 38, 38,  38] - initial guess for cap: 38
wallet: 36
nextGuess: 38 + 16 / 4 = 47
[2, 47, 47, 47, 47]
47 <= 50 -> stop
*/

int main() {
	vector<int> grantsArray = {2, 100, 50, 120, 1000}; // ans: 47
	int newBudget = 190;

	double ans = findGrantsCap(grantsArray, newBudget);
	cout << "Answer: " << ans << endl;
	return 0;
}