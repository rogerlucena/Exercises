#include <iostream>
#include <vector>

using namespace std;

// https://neetcode.io/problems/string-encode-and-decode?list=neetcode150

// Design an algorithm to encode a list of strings to a single string. The encoded string is then decoded back to the original list of strings.
// Please implement encode and decode

// Example 1:
// Input: ["neet","code","love","you"]
// Output:["neet","code","love","you"]

// Constraints:
// 0 <= strs.length < 100
// 0 <= strs[i].length < 200
// strs[i] contains only UTF-8 characters.


// Good to practice strings and substr, remember when appending strings to use += for better performance as below (just appending, 
// not unecessarily recopying the first str too).

// Clever way appending the size of the string first in the code before '#', this way can extract the substr with no problems
// after the first '#' (that came just after the size) even if that substr contains the separator '#'.
// The way below it avoids going through the entire code with the indexes, like 1000#longstring... jumps the "longstring..." part, 
// but it will still pass through it when getting the substr.
string encode(vector<string>& strs) {
    string code;
    for (const string& s : strs) {
        code += to_string(s.size()) + "#" + s;
    }

    return code;
}

vector<string> decode(string s) {
	vector<string> ans;

    int i = 0;
    while (i < s.size()) {
        int j = i;
        while (s[j] != '#') {
            ++j;
        }
        int length = stoi(s.substr(i, j - i));
        ans.push_back(s.substr(j + 1, length));
        i = j + length + 1;
    }

    return ans;
}

// The way below does not work when one of the strings has the separator char '#', 
// the way above appending the size first (a number before '#') does not have this weakness.
/*
string encode(vector<string>& strs) {
    string code;
    for (const string& s : strs) {
        code += s + "#";
    }

    return code;
}

vector<string> decode(string s) {
	vector<string> ans;

    int i = 0;
	while (i < s.size()) {
		int j = i;
		while (s[j] != '#') {
			++j;
		}
        ans.push_back(s.substr(i, j - i));
        i = j + 1;
    }

    return ans;
}
*/

int main() {
	cout << "Hello, World!";
	return 0;
}