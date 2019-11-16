#include <iostream>
#include <string>
#include <vector>

#include "tools.cpp"

using namespace std;

// https://www.pramp.com/challenge/5j2xWAx1qPtlZGLnG2O0

// Diff Between Two Strings (make A become B - only add and delete allowed)

// Given two strings of uppercase letters source and target, list (in string form) a sequence of edits to 
// convert from source to target that uses the least edits possible.

// For example, with strings source = "ABCDEFG", and target = "ABDFFGH" we might 
// return: ["A", "B", "-C", "D", "-E", "F", "+F", "G", "+H"
// More formally, for each character C in source, we will either write the token C, which does 
// not count as an edit; or write the token -C, which counts as an edit.
// Additionally, between any token that we write, we may write +D where D is any letter, which counts as an edit.

// At the end, when reading the tokens from left to right, and not including tokens prefixed with a minus-sign, 
// the letters should spell out target (when ignoring plus-signs.)
// In the example, the answer of A B -C D -E F +F G +H has total number of edits 4 (the minimum possible), 
// and ignoring subtraction-tokens, spells out A, B, D, F, +F, G, +H which represents the string target.
// If there are multiple answers, use the answer that favors removing from the source first.

// Constraints:

// [time limit] 5000ms
// [input] string source
// 2 ≤ source.length ≤ 12
// [input] string target
// 2 ≤ target.length ≤ 12
// [output] array.string


int fillMemoWithNEdits(const string &a, int ia, const string &b, int ib, vector<vector<int>> &memo) {
	if(memo[ia][ib] != -1) {
		return memo[ia][ib];
	}
	
	if(ia == a.size()) {
		memo[ia][ib] = b.size() - ib;
	} else if(ib == b.size()) {
		memo[ia][ib] = a.size() - ia;
	} else if(a[ia] == b[ib]) {
		memo[ia][ib] = fillMemoWithNEdits(a, ia+1, b, ib+1, memo);
	} else {
		int withDel = 1 + fillMemoWithNEdits(a, ia+1, b, ib, memo);
		int withAdd = 1 + fillMemoWithNEdits(a, ia, b, ib+1, memo);
		memo[ia][ib] = withDel <= withAdd ? withDel : withAdd;
	}

	return memo[ia][ib];
}

void fillAns(const string &a, int ia, const string &b, int ib, vector<vector<int>> &memo, vector<string> &ans) {
	if(ia == a.size()) {
		while(ib != b.size()) {
			ans.push_back("+" + string(1, b[ib]));
			++ib;
		}
	} else if(ib == b.size()) {
		while(ia != a.size()) {
			ans.push_back("-" + string(1, a[ia]));
			++ia;
		}
	} else if(a[ia] == b[ib]) {
		ans.push_back(string(1, a[ia]));
		fillAns(a, ia+1, b, ib+1, memo, ans);
	} else {
		if(memo[ia+1][ib] <= memo[ia][ib+1]) {
			ans.push_back("-" + string(1, a[ia]));
			fillAns(a, ia+1, b, ib, memo, ans);
		} else {
			ans.push_back("+" + string(1, b[ib]));
			fillAns(a, ia, b, ib+1, memo, ans);
		}
	}
}

vector<string> diffBetweenTwoStrings(const string &source, const string &target) {
	vector<vector<int>> memo(source.size()+1, vector<int>(target.size()+1, -1));
  	fillMemoWithNEdits(source, 0, target, 0, memo);
	
	vector<string> ans;
	fillAns(source, 0, target, 0, memo, ans);

	return ans;
}


int main() {
	string source = "ABCDEFG"; // "ABB";
	string target = "ABDFFGH"; // "AAB";

	cout << "Answer:" << endl;
	auto printEl = [](const string &s) -> void{cout << s;};
	printVector<string>(diffBetweenTwoStrings(source, target), printEl);

	return 0;
}