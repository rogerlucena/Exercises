#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/explore/other/card/30-day-leetcoding-challenge/530/week-3/3306/

// A binary matrix means that all elements are 0 or 1. For each individual row of the matrix, this row 
// is sorted in non-decreasing order.

// Given a row-sorted binary matrix binaryMatrix, return leftmost column index(0-indexed) with at least a 1 
// in it. If such index doesn't exist, return -1.

// You can't access the Binary Matrix directly.  You may only access the matrix using a BinaryMatrix interface:

// BinaryMatrix.get(x, y) returns the element of the matrix at index (x, y) (0-indexed).
// BinaryMatrix.dimensions() returns a list of 2 elements [n, m], which means the matrix is n * m.
// Submissions making more than 1000 calls to BinaryMatrix.get will be judged Wrong Answer.  Also, any solutions 
// that attempt to circumvent the judge will result in disqualification.

// For custom testing purposes you're given the binary matrix mat as input in the following four examples. You will 
// not have access the binary matrix directly.

 class BinaryMatrix {
   public:
     int get(int x, int y);
     vector<int> dimensions();
 };

int getLeftmostOne(BinaryMatrix &binaryMatrix, int i, int from, int to) {
	if(from > to) {
		return binaryMatrix.dimensions()[1];
	}

	int mid = (from + to) / 2;
	if(binaryMatrix.get(i, mid) == 1) {
		if(mid == 0 || binaryMatrix.get(i, mid-1) == 0) {
			return mid;
		} else {
			return getLeftmostOne(binaryMatrix, i, from, mid-1);
		}
	} else {
		return getLeftmostOne(binaryMatrix, i, mid + 1, to);
	}

}

int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
	vector<int> dim = binaryMatrix.dimensions();
	int leftmost = dim[1];

	for(int i = 0; i < dim[0]; ++i) {
		leftmost = min(leftmost, getLeftmostOne(binaryMatrix, i, 0, dim[1] - 1));
	}

	return leftmost == dim[1] ? -1 : leftmost;
}

int main() {
	cout << "Hello, World!";
	return 0;
}