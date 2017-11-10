#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

/*

-- Problem statement:

- Print present numbers.

You receive a list with natural numbers in [1,100] and you wanna output in a readable
way the numbers that are present.

INPUT: vector<int> numbers
OUTPUT: vector<string> gaps

 e.g. INPUT  = [1,2,3,4,5,10,12,50]
      OUTPUT = ["1-5", "10", "12", "50"]


- Follow up: print the missing intervals:
OUTPUT = ["6-9","11","13-49","51-100"] -> missing ones

*/

// Solution O(nlogn) in time and O(1) in space (not considering the space for "gaps")

void fillGaps(vector<int> numbers, vector<string> &gaps){
    int prevIndex = 0;
    for (int i = 1; i < numbers.size(); ++i) {
        if(numbers.at(i)-numbers.at(i-1)>1){
            if(prevIndex==i-1){
                char* resc;
                sprintf(resc, "\"%d\"", numbers[prevIndex]);
                string res(resc);
                gaps.push_back(res);
            }
            else{
                char* resc;
                sprintf(resc, "\"%d-%d\"", numbers[prevIndex], numbers[i-1]);
                string res(resc);
                gaps.push_back(res);
            }
            prevIndex = i;
        }
        else{

        }
    }
}

int main()
{
    // They must be in the interval [1, 100]
    vector<int> numbers = {100, 99, 50, 15, 14, 13, 12, 10, 5, 4, 3, 2, 1};
    numbers.push_back(INT_MAX); // dumb value

    vector<string> gaps;

    sort(numbers.begin(), numbers.end());
    fillGaps(numbers, gaps);

    cout << "[ ";
    for(string s : gaps){
        cout << s << " ";
    }
    cout << "]" << endl;


    return 0;
}

