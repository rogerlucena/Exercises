#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/reverse-the-string/

// Given a string A.
// Return the string A after reversing the string word by word.

// NOTE:
// A sequence of non-space characters constitutes a word.
// Your reversed string should not contain leading or trailing spaces, even if it is present in the input string.
// If there are multiple spaces between words, reduce them to a single space in the reversed string.

// For Example:

// Input 1:
//     A = "the sky is blue"
// Output 1:
//     "blue is sky the"

// Input 2:
//     A = "this is ib"
// Output 2:
//     "ib is this"

void swapInterval(string &s, int i, int j) {
	if(i >= j) {
		return;
	}

	int mid = (i + j)/2;
	for(int k = 0; k <= mid-i; ++k) {
		swap(s[i+k], s[j-k]);
	}
}

string solve(string A) {
	if(A.empty() || A.size() == 1) {
		return A;
	}

	int size = A.size();
	for(int i = 0; i < size/2; ++i) {
		swap(A[i], A[size-1-i]);
	}

	int i = 0;
	for(int j = 0; j <= size; ++j) {
		if(j == size || A[j] == ' ') {
			swapInterval(A, i, j-1);
			i = j+1;
		}
	}

	return A;
}


int main() {
	cout << "Hello, World!";
	return 0;
}