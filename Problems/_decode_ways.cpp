#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/decode-ways
// https://www.tryexponent.com/practice/prepare/decode-variations
// Remember: do not forget the edge case of '0', and check the chars as below instead of using substr and stoi.

// You have intercepted a secret message encoded as a string of numbers. The message is decoded via the 
// following mapping:

// "1" -> 'A'

// "2" -> 'B'

// ...

// "25" -> 'Y'

// "26" -> 'Z'

// However, while decoding the message, you realize that there are many different ways you can decode 
// the message because some codes are contained in other codes ("2" and "5" vs "25").

// For example, "11106" can be decoded into:

// "AAJF" with the grouping (1, 1, 10, 6)
// "KJF" with the grouping (11, 10, 6)
// The grouping (1, 11, 06) is invalid because "06" is not a valid code (only "6" is valid).
// Note: there may be strings that are impossible to decode.

// Given a string s containing only digits, return the number of ways to decode it. If the entire string 
// cannot be decoded in any valid way, return 0.
// The test cases are generated so that the answer fits in a 32-bit integer.

// Example:
// Input: s = "12"
// Output: 2
// Explanation:
// "12" could be decoded as "AB" (1 2) or "L" (12).

// Bottom-up:
int numDecodings(string s) {
    int n = s.size();
    vector<int> memo(n + 1, 0);
    memo[n] = 1;
    memo[n - 1] = s[n - 1] != '0';
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] == '0') {
            continue;
        }
        memo[i] = memo[i + 1];  // for all chars from '1' to '9'.
        if (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6')) {
            memo[i] += memo[i + 2];
        }
    }

    return memo[0];
}

// Top-down:
int numDecodingsRecursive(const string& s, int i, vector<int>& memo) {
    if (i >= s.size()) {
        return 1;
    }
    if (memo[i] != -1) {
        return memo[i];
    }

    if (s[i] == '0') {
        memo[i] = 0;
        return memo[i];
    }

    memo[i] = numDecodingsRecursive(s, i + 1, memo);  // for all chars from '1' to '9'.
    int len = s.size();
    if (i < len - 1 && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
        memo[i] += numDecodingsRecursive(s, i + 2, memo);
    }

    return memo[i];
}

int numDecodingsTopDown(string s) {
    vector<int> memo(s.size(), -1);
    return numDecodingsRecursive(s, 0, memo);
}

int main() {
	cout << "Hello, World!";
	return 0;
}