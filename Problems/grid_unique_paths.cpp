#include <iostream>
#include <math.h>
#include <unordered_map>

using namespace std;

// https://www.interviewbit.com/problems/grid-unique-paths/

// The robot can only move either down or right at any point in time. The robot is trying to 
// reach the bottom-right corner of the grid (marked ‘Finish’ in the diagram below).
// How many possible unique paths are there?

int fact(int n, unordered_map<int, int> &factorials) {
	if(factorials.find(n) != factorials.end()) {
		return factorials[n];
	}
	int ans = n * fact(n-1, factorials);
	factorials[n] = ans;
	cout << n << " : " << ans << endl;
	return ans;
}

// Interesting way of calculating binomial coeffs:
// https://www.geeksforgeeks.org/binomial-coefficient-dp-9/
int binomialCoeff(int n, int k) { 
    int C[k+1]; 
    memset(C, 0, sizeof(C)); 
  
    C[0] = 1;  // nC0 is 1 
  
    for (int i = 1; i <= n; i++) { 
        // Compute next row of pascal triangle using 
        // the previous row 
		// (if "k" is min, you can optimize and compute till "k" only, else you compute 
		// till n because it is the max size of that pascal row)
        for (int j = min(i, k); j > 0; j--) {
            C[j] = C[j] + C[j-1]; 
		}
    } 
    return C[k]; 
} 

int uniquePaths(int A, int B) {
	int downSteps = A-1;
	int rightSteps = B-1;

	return binomialCoeff(downSteps+rightSteps, min(downSteps, rightSteps));
}

int uniquePaths2(int A, int B) {
	int downSteps = A-1;
	int rightSteps = B-1;

	unordered_map<int, int> factorials;
	factorials[0] = 1;
	factorials[1] = 1;
	return fact(downSteps+rightSteps, factorials)/(fact(downSteps, factorials)*fact(rightSteps, factorials));
}

int main() {
	cout << "Answer:" << endl << uniquePaths(100, 1) << endl;
	return 0;
}