#include <bits/stdc++.h>

using namespace std;
/*

-- Problem statement:

Given a string , find the number of "unordered anagrammatic pairs" of substrings.
In other words, find the number of unordered pairs of substrings of  that are anagrams of each other.

Two strings are anagrams of each other if the letters of one string can be rearranged to form the other string.

Input Format
First line contains , the number of testcases. Each testcase consists of string  in one line.

Constraints
String  contains only the lowercase letters of the English alphabet.

Output Format
For each testcase, print the required answer in one line.

Sample Input
2
abba
abcd

Sample Output
4
0

*/

int nChoosek( int n, int k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

int sherlockAndAnagrams(string s){
    // Complete this function
    unordered_map<string, int> m;

    int n = s.length();
    for(int i=0; i<n; ++i){
        for(int len=1; len<=n-i; ++len){
            string ss = s.substr(i, len);
            //cout << "substring: " << ss << endl;
            sort(ss.begin(), ss.end());
            if(m.find(ss) != m.end()) m[ss] +=1;
            else m[ss] = 1;
        }
    }

    int count = 0;
    for(auto it = m.begin(); it != m.end(); ++it){
        if(it->second > 1) {
            //cout << "repeated: " << it->first << "  times: " << it-> second << endl;
            count += nChoosek(it->second, 2);
        }
    }

    return count;
}

int main() {
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        std::string s;
        cin >> s;
        int result = sherlockAndAnagrams(s);
        cout << result << endl;
    }
    return 0;
}
