#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

// mymap.clear() - delete everything

// mymap.find(key_value) - it is mymap.end() if not found
// for (auto &p : mymap) cout << p.first << " " << p.second << endl;
// mymap["newkey_value"] = "newobj_value";
// mymap.size()  // O(1)

// Erasing:
// if (mymap.find(key) != mymap.end()) 
//    mymap.erase(mymap.find(key)); // return "it" just following the last deleted element
// OR mymap.erase(key); // return an int - number of elements deleted, 0 if not key found in mymap
// OR mymap.erase(mymap.begin(()); // erasing only one element, return "it" just following
// OR mymap.erase(mymap.begin(), mymap.end()) - erase everything

template <class T1, class T2>
class myPair {
    public:
    T1 t1_;
    T2 t2_;
        myPair(T1 t1, T2 t2): t1_(t1), t2_(t2) {};
};

int main() {
    unordered_map <string, int> m;

    //m["foo"] = 42;
    //cout << m["foo"] << endl;

    // Another ways to start a has_map
    /*
    std::unordered_map<std::string,double> mymap = {
            {"mom",5.4},
            {"dad",6.1},
            {"bro",5.9} };
    */


    std::unordered_map<std::string,double> mymap = {
        {"mom",5.4},
        {"dad",6.1},
        {"bro",5.9} 
    };

    std::string input = "Roger";
    std::cout << "who? --> input = Roger";

    std::unordered_map<std::string,double>::const_iterator got = mymap.find(input);
    //unordered_map<string, double>::iterator it;

    if ( got == mymap.end() )
        std::cout << "not found";
    else
        std::cout << got->first << " is " << got->second;

    std::cout << std::endl;


    // Iteration over the unordered_map:
    unordered_map<string, int> mymap2 = {
      {"roger", 1995},
      {"renner", 1997}
    };

    mymap2["neuma"] = 1968;

    for (auto p : mymap2) { // a c++ pair<string, int>
        cout << p.first << " was born in " << p.second << endl;
    }

    // Another way of iterating
    for (auto it = mymap2.begin(); it != mymap2.end(); ++it) {
        cout << it->first << " " << it->second << endl;
        if(false) {
            mymap2.erase(it); // how to erase, remember that after erasing curr it ->
                              // -> it will receive it+1 (C++11 or newer) - problem with the ++it of the "for" 
            // you should then transform the for into a while and do mymap.erase(it++) (increment and then return the old)
        }
    }

    // Constains of hash_map in C++
    // Find a key (contains) -> syntax
    std::unordered_map<std::string,double>::const_iterator got2 = mymap.find (input);

    if (got2 == mymap.end()) std::cout << "not found";
    else std::cout << got2->first << " is " << got2->second;

    cout << "Testing my template class of Pairs:" << endl;
    myPair<string, int> p("oi", 37);
    cout << "My pair: (" << p.t1_<< ", " << p.t2_ << ")"<< endl;

    cout << "size: " << mymap2.size() << endl;
    cout << "begin: " << mymap2.begin()->first << endl;
    mymap2.erase(mymap2.begin());
    cout << "size: " << mymap2.size() << endl;
    cout << "begin: " << mymap2.begin()->first << endl;

    return 0;
}