#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

/*

 -- Problem Statement: https://leetcode.com/problems/group-anagrams/description/
 Basically, from a vector of strings, group all the anagrams together

*/

using namespace std;

string genUniqueString(string s) {
    int occ [26] = {0}; // Fill with zeros
    string sol;
    for(char c : s) {
        occ[c-'a']++;
    }
    for(int i=0; i<26; ++i){
        if(occ[i]>0) {
            sol.push_back('a'+i); // ASCII
            ostringstream aux; aux << occ[i];
            sol.append(aux.str());
        }
    }
    return sol;
}

// time: O(n*m), space: O(n*m)
vector<vector<string>> groupAnagrams (vector<string> l) {
    unordered_map<string, vector<string>> map;
    vector<string> labels;
    vector<vector<string>> solution;

    for(string s : l) {
        string unique = genUniqueString(s);
        if(map.find(unique) != map.end()){
            map[unique].push_back(s);
        }
        else{
            vector<string> vString;
            vString.push_back(s);
            map[unique] = vString;
            labels.push_back(unique);
        }
    }

    for(string u : labels){
        solution.push_back(map.find(u)->second);
    }

    return solution;
}


int main()
{
    vector<string> l = {"word", "rdow", "second", "ab", "ba", "tuua", "utua", "autu"};
    vector<vector<string>> solution = groupAnagrams(l);

    for(vector<string> vS : solution) {
        for(string s: vS) {
            cout << "\"" << s << "\"" << " ";
        }
        cout << endl;
    }

    return 0;
}