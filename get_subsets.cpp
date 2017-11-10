#include <iostream>
#include <set>

using namespace std;

/*

Generating recursively subsets out of original set

*/

void getSubsets(set<int>  myset, set<set<int>> &mySubsets) {
    if(myset.size() == 0){
        set<int> emptySet;
        mySubsets.insert(emptySet);
    }
    else{
        set<set<int>> auxSubsets;
        auto beg = myset.begin();
        int fst = *beg;
        myset.erase(beg);
        getSubsets(myset, auxSubsets);
        for(set<int> s : auxSubsets) {
            mySubsets.insert(s);
            s.insert(fst);
            mySubsets.insert(s);
        }
    }
}

int main() {
    set<int> mySet = {1, 2};
    set<set<int>> mySubsets;
    getSubsets(mySet, mySubsets);
    for(auto s : mySubsets){
        cout << "Subset: " ;
        for(int i : s){
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}