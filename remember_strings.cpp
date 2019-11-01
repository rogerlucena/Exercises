#include <iostream>
#include <string>

using namespace std;

/*
    // To understand a number as string (int -> string)
    use std::to_string(number);

    // Syntax of ostringstream (previous way of doing int -> string)
    int a=55;
    std::ostringstream aux;
    aux << a;
    cout << "char aux is: " << aux.str() << endl;

    Notes:

    char c = int('a' + 1); // 'b'
	char c = char('9' - 1); // '8'
*/

int main ()
{
    // string s = "eu sou o roger lindao";
    // int pos = s.find("roger");
    // cout << "size_t pos is: " << pos << endl;
    // string new_s = s.substr(9); // "roger lindao"
    // cout << "new_s: " << new_s << endl;

    // .push_back() and .pop_back() -> only for chars              --- O(1), constant amortized time (good)
    // .append(string a) ; or " += " -> only to append strings,    --- O(n), linear complexity on the size of the new string (bad)
    // str.append("dots are cool", 5); // "dots "

    char line[] = "short line for testing";

    cout << "- Basic string operations:" << endl;
    // with no arguments
    string s1;
    s1 = "Anatoliy";
    cout << "s1  is: " << s1 << endl; // s1  is: Anatoliy

    // copy constructor
    string s2 (s1);
    cout << "s2  is: " << s2 << endl; // s2  is: Anatoliy

    // one argument, array of chars
    string s3 (line);
    cout << "s3  is: " << s3 << endl; // s3  is: short line for testing

    // first argumen C string
    // start position
    string s4 (line, 10);
    cout << "s4  is: " << s4 << endl; // s4  is:  for testing

    // 1 - C++ string
    // 2 - start position
    // 3 - number of characters
    string s5 (s3, 6, 4); // copy word 'line' from s3
    cout << "s5  is: " << s5 << endl; // s5  is: line

    // 1 - number characters
    // 2 - character itself
    // repeating it
    string s6 (15, '*');
    cout << "s6  is: " << s6 << endl; // s6  is: ***************

    // 1 - start iterator
    // 2 - end iterator [) - opened interval at the end
    string s7 (s3.begin(), s3.end()-5); 
    cout << "s7  is: " << s7 << endl; // s7  is: short line for te


    // you can instantiate string with assignment
    string s8 = "Anatoliy";
    cout << "s8  is: " << s8 << endl << endl; // s8  is: Anatoliy


    // Some additional tests:
    // size; at == [] just like a vector
    cout << "- Some additional tests:" << endl;
    cout << "First letter of s8: " << s8[0] << endl; // First letter of s8: A
    cout << "Size of s8: " << s8.size() << endl; // .legth() produces the same thing
    cout << "Chars in s8: " << endl;
    for(char c : s8){
        cout << c << " ";
    }
    cout << endl;

    int sz = s8.size();
    s8.resize (sz + 2, '+');
    std::cout << "new s8: " << s8 << '\n'; // new s8: Anatoliy++
    s8.clear(); // normally constant time, becomes an empty string
    cout << "new new s8: " << s8 << endl << endl; // new new s8:


    // Substring:
    cout << "- Playing with substrings:" << endl;
    std::string str = "We think in generalities, but we live in details."; // (quoting Alfred N. Whitehead)
    std::string str2 = str.substr(3, 5);     // "think"
    std::size_t pos = str.find("live");      // position of "live" in str, 
    cout << "pos: " << pos << endl;          // pos: 33
    std::string str3 = str.substr(pos);     // get from "live" to the end
    std::cout << str2 << " // " << str3 << endl;
    cout << endl;


    // Playing with the insert method below:
    cout << "- Playing with the insert:" << endl;
    std::string strn="to be question"; // strn = str new (renaming)
    std::string str2n="the ";
    std::string str3n="or not to be";
    std::string::iterator it;

    // used in the same order as described above:
    strn.insert(6, str2n);                 // to be (the )question   ; specify position
    strn.insert(6, str3n, 3, 4);           // to be (not )the question, initial position + pos andsize of the second
    cout << "strn: " << strn << endl;
    strn.insert(10, "that is cool", 8);    // to be not (that is )the question
    strn.insert(10, "to be ");             // to be not (to be )that is the question
    strn.insert(15, 1, ':');               // to be not to be(:) that is the question
    it = strn.insert(strn.begin()+5, ','); // to be(,) not to be: that is the question   ; it points just to a char 
    cout << "it: " << *(it) << endl;       // it: ,
    cout << "it: " << *(it+3) << endl;     // it: o
    strn.insert(strn.end(), 3, '.');       // to be, not to be: that is the question(...)
    strn.insert(it+2, str3n.begin(), str3n.begin()+3); // (or )

    cout << "strn: " << strn << endl;      // strn: to be, or not to be: that is the question...
    cout << "final size: " << strn.size() << endl; // final size: 44

    return 0;
}