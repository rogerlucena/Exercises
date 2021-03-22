#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/

// There are several cards arranged in a row, and each card has an associated number of points.
// The points are given in the integer array cardPoints.
// In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.
// Your score is the sum of the points of the cards you have taken.
// Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

// O(k) in time and O(1) in space.
int maxScore(vector<int>& cardPoints, int k) {
	int accRight = 0;
	int nCards = cardPoints.size();
	for(int j = 1; j <= k; ++j) {
		accRight += cardPoints[nCards - j]; // total for "k" advances on the right
	}

	int accLeft = 0;
	int maxPoints = accRight; // "i" being 0 and "j" being k is already taken into account here
	for(int i = 1; i <= k; ++i) { // "i" is the total number of advances on the left, "j" is for the right
		int j = k - i;
		accLeft += cardPoints[i-1];
		accRight -= cardPoints[nCards-j-1];
		maxPoints = max(maxPoints, accLeft + accRight);
	}

	return maxPoints;
}

// O(k) in time and space, can be improved to O(1) in space. 
int maxScoreBadSpace(vector<int>& cardPoints, int k) {
	vector<int> left(k+1, 0);
	vector<int> right(k+1, 0);
	int nCards = cardPoints.size();

	for(int i = 1; i <= k; ++i) {
		left[i] = left[i-1] + cardPoints[i-1];
	}
	for(int j = 1; j <= k; ++j) {
		right[j] = right[j-1] + cardPoints[nCards-j];
	}

	int maxPoints = 0;
	for(int i = 0; i <= k; ++i) {
		maxPoints = max(maxPoints, left[i] + right[k-i]);
	}

	return maxPoints;
}

// Unnecessarily slow, O(k^2 / 2), can be reduced to O(k) calculating only the principal secondary diagonal
int maxScoreDP(vector<int>& cardPoints, int k) {
	unordered_map<int, unordered_map<int, int>> accPoints;
	int nCards = cardPoints.size();
	for (int i = 0; i <= k; ++i) {
		for (int j = 0; j <= k-i; ++j) {
			int points = 0;
			if (i - 1 >= 0) {
				points = max(points, accPoints[i-1][j] + cardPoints[i-1]);
			}
			if (j - 1 >= 0) {
				points = max(points, accPoints[i][j-1] + cardPoints[nCards - j]);
			}
			accPoints[i][j] = points;
		}
	}

	int maxPoints = 0;
	for(int i = 0, j = k; i <= k; ++i, --j) {
		maxPoints = max(maxPoints, accPoints[i][j]);
	}
	
	return maxPoints;
}

int main() {
	vector<int> cardPoints = {1,2,3,4,5,6,1}; // ans: 12
	int k = 3;

	int ans = maxScore(cardPoints, k);
	cout << "Answer: " <<  ans << endl;

	return 0;
}