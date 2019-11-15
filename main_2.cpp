#include <iostream>
#include <vector>

using namespace std;

int main() {
	cout << "Hello, World!";
	return 0;
}








// #include <iostream>
// #include <vector>

// using namespace std;

// int isMatchHelper(const string &A, int ia, const string &B, int ib, vector<vector<int>> &m) {
// 	if(m[ia][ib] != -1) {
// 		return m[ia][ib];
// 	}
	
// 	if(ia < A.size() && A[ia] == '*') {
// 		// int ans = 0;
// 		// for(int i = 0; !ans && (i == 0 || ib+i <= B.size()); ++i) {// || (ib+i < B.size() && B[ib+i] == B[ib+i-1])); ++i) {
// 		// 	ans = ans || isMatchHelper(A, ia+1, B, ib+i, m);
// 		// }
// 		m[ia][ib] = (ib < B.size() && isMatchHelper(A, ia, B, ib+1, m)) || isMatchHelper(A, ia+1, B, ib, m);
// 	} else if(ib < B.size() && B[ib] == '*') {
// 		// int ans = 0;
// 		// for(int i = 0; !ans && (i == 0 || ia+i <= A.size()); ++i) { // || (ia+i < A.size() && A[ia+i] == A[ia+i-1])); ++i) {
// 		// 	ans = ans || isMatchHelper(A, ia+i, B, ib+1, m);
// 		// }
// 		m[ia][ib] = (ia < A.size() && isMatchHelper(A, ia+1, B, ib, m)) || isMatchHelper(A, ia, B, ib+1, m);
// 	} else if(ia == A.size() || ib == B.size()) {
// 		m[ia][ib] = ia == A.size() && ib == B.size();
// 	} else if(A[ia] == '?' || B[ib] == '?' || A[ia] == B[ib]) {
// 		m[ia][ib] = isMatchHelper(A, ia+1, B, ib+1, m);
// 	} else {
// 		m[ia][ib] = false;
// 	}

// 	return m[ia][ib];
// }

// int isMatch(const string A, const string B) {
// 	vector<vector<int>> m (A.size()+1, vector<int>(B.size()+1, -1));
// 	return isMatchHelper(A, 0, B, 0, m);
// }


// int main() {
// 	vector<string> A = {"aa", "aa", "aaa", "aa", "aa", "ab", "aab"};
//     vector<string> B = {"a",  "aa", "aa",  "*",  "a*", "?*", "c*a*b"};
// 	vector<int>  res = {0,    1,    0,     1,    1,     1,   0};
	
// 	int i = 0;
// 	for(; i < A.size(); ++i) {
// 		if(isMatch(A[i], B[i]) != res[i]) {
// 			cout << "Problem in case: " << i << endl;
// 			break;
// 		}
// 	}

// 	if(i == A.size()) {
// 		cout << "Program passed all the tests" << endl;
// 	}


// 	return 0;
// }