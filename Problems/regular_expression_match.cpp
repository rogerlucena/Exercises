#include <iostream>
#include <vector>

using namespace std;

// https://www.interviewbit.com/problems/regular-expression-match/

// Implement wildcard pattern matching with support for ‘?’ and ‘*’ for strings A and B.

// ’?’ : Matches any single character.
// ‘*’ : Matches any sequence of characters (including the empty sequence).
// The matching should cover the entire input string (not partial).

// Input Format:
// The first argument of input contains a string A.
// The second argument of input contains a string B.
// Output Format:

// Return 0 or 1:
//     => 0 : If the patterns do not match.
//     => 1 : If the patterns match.

// Constraints:
// 1 <= length(A), length(B) <= 9e4

// Examples :

// Input 1:
//     A = "aa"
//     B = "a"
// Output 1:
//     0

// Input 2:
//     A = "aa"
//     B = "aa"
// Output 2:
//     1

// Input 3:
//     A = "aaa"
//     B = "aa"
// Output 3:
//     0
    
// Input 4:
//     A = "aa"
//     B = "*"
// Output 4:
//     1

// Input 5:
//     A = "aa"
//     B = "a*"
// Output 5:
//     1

// Input 6:
//     A = "ab"
//     B = "?*"
// Output 6:
//     1

// Input 7:
//     A = "aab"
//     B = "c*a*b"
// Output 7:
//     0

// Website solution
int isMatch(const string a, const string b) {
    int i,j;
    int n = a.size();
    int m = b.size();

    vector<vector<bool>> dp(n+1, vector<bool>(m+1));
    dp[0][0] = true;
    for(i=1; i<=m; i++) {
        dp[0][i] = false;
        if(b[i-1]=='*' && (i-1==0 || (i>=1 && b[i-2]=='*'))) {
            dp[0][i]=dp[0][i-1];
        }
    }
    for(j=1;j<=n;j++)
    {
        dp[j][0]=false;
    }
    
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            if(b[j-1]=='?')
            {
                dp[i][j]=dp[i-1][j-1];
            }
            else if(b[j-1]=='*')
            {
                dp[i][j]=dp[i-1][j]||dp[i][j-1];
            }
            else 
            {
                dp[i][j]=(a[i-1]==b[j-1])&&dp[i-1][j-1];
            }
        }
    }

    return (dp[n][m]==true)?1:0;
    
}

int main() {
	cout << "Hello, World!";
	return 0;
}