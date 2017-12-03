#include <unordered_map>
//#include <hash_map>
#include <iostream>
#include <string>

using namespace std;
//using namespace __gnu_cxx;

template <class T1, class T2>
class myPair{
    public:
    T1 t1_;
    T2 t2_;
        myPair(T1 t1, T2 t2): t1_(t1), t2_(t2) {};
};

int main2() {
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
        {"bro",5.9} };

    std::string input = "Roger";
    std::cout << "who? --> input = Roger";

    std::unordered_map<std::string,double>::const_iterator got = mymap.find (input);

    if ( got == mymap.end() )
        std::cout << "not found";
    else
        std::cout << got->first << " is " << got->second;

    std::cout << std::endl;



    // Training:
    int n;
    cin >> n;
    string curr;
    for(int i=1; i<=n; ++i){
        cin >> curr;
        int initialLenght = curr.length();
        char last = curr.at(initialLenght-1);
        int j = 1;
        while(m.find(curr) != m.end()){
            string aux = to_string(j);
            int currLength = curr.length();
            if(currLength != initialLenght)
                curr = curr.substr(0, currLength-1);
            curr.append(aux);
            ++j;
        }
        if(curr.at(curr.length()-1) == last) {
            m[curr] = 1;
            cout << "OK" << endl;
        }
        else {
            m[curr] = 2;
            cout << curr << endl;
        }
    }

    // Iteration over the unordered_map:
    /*
    for(auto it = m.begin(); it != m.end(); ++it){
        if()
        cout << it->first << endl; // key
    }
    */


    // Constains of hash_map in C++
    // Find a key (contains) -> syntax
    /*
    std::unordered_map<std::string,double>::const_iterator got = mymap.find (input);

    if ( got == mymap.end() )
        std::cout << "not found";
     else
        std::cout << got->first << " is " << got->second;
    */

    /*
    cout << "Testing my template class of Pairs:" << endl;
    myPair<string, int> p("oi", 37);
    cout << "My pair: (" << p.t1_<< ", " << p.t2_ << ")"<< endl;
    */
}