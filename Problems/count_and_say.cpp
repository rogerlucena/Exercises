#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/count-and-say/

// The count-and-say sequence is the sequence of integers beginning as follows:
// 1, 11, 21, 1211, 111221, ...

// 1 is read off as one 1 or 11.
// 11 is read off as two 1s or 21.
// 21 is read off as one 2, then one 1 or 1211.

// Task: Given an integer n, generate the nth sequence.

// Example:
// if n = 2, the sequence is 11.

string getNext(const string &s) {
	if(s.size() == 1) {
		return "11";
	}

	string ans = "";
	int count = 1;
	char prevChar = s[0];
	for(int i = 1; i < s.size(); ++i) {
		while(s[i] == prevChar && i < s.size()) {
			++i;
			++count;
		}
		for(char c : to_string(count)) {
			ans.push_back(c);
		}
		ans.push_back(prevChar);

		if(i < s.size() - 1) {
			count = 1;
			prevChar = s[i];
		} else if(i == s.size() - 1) {
			ans.push_back('1');
			ans.push_back(s[i]);
		}
	}

	return ans;
}

string countAndSay(int A) {
	string ans = "1";
	for(int i = 2; i <= A; ++i) {
		ans = getNext(ans);
		// cout << "i: " << i << ", ans: " << ans << endl;
	}

	return ans;
}


int main() {
	int n = 5;
	cout << "Answer: " << countAndSay(n);

	return 0;
}