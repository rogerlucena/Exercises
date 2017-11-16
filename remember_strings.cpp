#include <iostream>
#include <string>
using namespace std;

/*
    // Syntax of ostringstream
    int a=55;
    std::ostringstream aux;
    aux << a;
    cout << "char aux is: " << aux.str() << endl;

*/

int main ()
{
    // push_back() and pop_back() -> only for chars
    // append(string a) -> only to append strings
    // str.append("dots are cool",5);          // "dots "

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


    // -------------------------------------
    // Playing with the insert method below:

    // Substring:
    std::string str="We think in generalities, but we live in details.";
    //std::string str2 = str.substr (3,5);     // "think" (start, size)
    //std::size_t pos = str.find("live");      // position of "live" in str
    //std::string str3 = str.substr (pos);     // get from "live" to the end

    std::string str="to be question";
    std::string str2="the ";
    std::string str3="or not to be";
    std::string::iterator it;

    // used in the same order as described above:
    str.insert(6,str2);                 // to be (the )question
    str.insert(6,str3,3,4);             // to be (not )the question, initial position and size of the second
    str.insert(10,"that is cool",8);    // to be not (that is )the question
    str.insert(10,"to be ");            // to be not (to be )that is the question
    str.insert(15,1,':');               // to be not to be(:) that is the question
    it = str.insert(str.begin()+5,','); // to be(,) not to be: that is the question
    str.insert (str.end(),3,'.');       // to be, not to be: that is the question(...)
    str.insert (it+2,str3.begin(),str3.begin()+3); // (or )

    std::cout << str << '\n';
    return 0;
}