#include <iostream>
#include <vector>
using namespace std;

// Code to return the number of ones in the bit representation of every number in a vector

int nOf1s(int n){ // int8_t
    int count = 0;
    while(n!=0){
        if(n&1)
            ++count;
        n >>= 1;
    }

    return count;
}

int main()
{
    vector<int> indexes(20, 0); // creating a vector of size 20 and with only zeros
    vector<int> numbers = {3, 6, 32, 22};
    vector<int> solution;

    for(auto i : numbers){
        solution.push_back(nOf1s(i));
    }

    for (auto i = 0; i < solution.size(); ++i) {
        cout << solution.at(i) << " " ;
    }

    return 0;
}

// Observations
// int64_t = signed with exactly 64 bits
// long = signed with at least 32 bits
// Integer limits: https://msdn.microsoft.com/en-us/library/296az74e.aspx