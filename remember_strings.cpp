#include <iostream>
#include <string>
using namespace std;

int main ()
{
    char *line = "short line for testing";

    // with no arguments
    string s1;
    s1 = "Anatoliy";
    cout << "s1  is: " << s1 << endl;

    // copy constructor
    string s2 (s1);
    cout << "s2  is: " << s2 << endl;

    // one argumen
    string s3 (line);
    cout << "s3  is: " << s3 << endl;

    // first argumen C string
    // second number of characters
    string s4 (line,10);
    cout << "s4  is: " << s4 << endl;

    // 1 - C++ string
    // 2 - start position
    // 3 - number of characters
    string s5 (s3,6,4); // copy word 'line' from s3
    cout << "s5  is: " << s5 << endl;

    // 1 - number characters
    // 2 - character itself
    // repeating it
    string s6 (15,'*');
    cout << "s6  is: " << s6 << endl;

    // 1 - start iterator
    // 2 - end iterator
    string s7 (s3.begin(),s3.end()-5);
    cout << "s7  is: " << s7 << endl;

    // you can instantiate string with assignment
    string s8 = "Anatoliy";
    cout << "s8  is: " << s8 << endl;

    // at and size
    cout << "---- Some additional tests:" << endl;
    cout << "First letter of s8: " << s8.at(0) << endl;
    cout << "Size of s8: " << s8.size() << endl;
    cout << "Chars in s8: " << endl;
    for(char c : s8){
        cout << c << " ";
    }

    // Substring:
    std::string str="We think in generalities, but we live in details.";
    //std::string str2 = str.substr (3,5);     // "think" (start, size)
    //std::size_t pos = str.find("live");      // position of "live" in str
    //std::string str3 = str.substr (pos);     // get from "live" to the end

    return 0;
}