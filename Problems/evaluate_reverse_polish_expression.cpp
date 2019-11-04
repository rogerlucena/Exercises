#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// https://www.interviewbit.com/problems/evaluate-expression/

// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
// Valid operators are +, -, *, /. Each operand may be an integer or another expression.

// Example:
// Input 1:
//     A =   ["2", "1", "+", "3", "*"]
// Output 1:
//     9
// Explaination 1:
//     starting from backside:
//     *: ( )*( )
//     3: ()*(3)
//     +: ( () + () )*(3)
//     1: ( () + (1) )*(3)
//     2: ( (2) + (1) )*(3)
//     ((2)+(1))*(3) = 9

int evalRPN(vector<string> &A) {
	stack<int> s;
	for(string c : A) {
		if(c == "+") {
			int b = s.top();
			s.pop();
			int a = s.top();
			s.pop();
			s.push(a+b);
		} else if(c == "-") {
			int b = s.top();
			s.pop();
			int a = s.top();
			s.pop();
			s.push(a-b);
		} else if(c == "*") {
			int b = s.top();
			s.pop();
			int a = s.top();
			s.pop();
			s.push(a*b);
		} else if(c == "/") {
			int b = s.top();
			s.pop();
			int a = s.top();
			s.pop();
			s.push(a/b);
		} else {
			int n = stoi(c, nullptr, 10);
			s.push(n);
		}
	}

	int ans = s.top();
	s.pop();
	assert(s.empty());
	return ans;
}


int main() {
	// vector<string> A = {"2", "1", "+", "3", "*"}; // ans expected: 9
	vector<string> A = {"4", "13", "5", "/", "+"}; // ans expected: 6
	cout << "Answer: " << evalRPN(A) << endl;

	return 0;
}