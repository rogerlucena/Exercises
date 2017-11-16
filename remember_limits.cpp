#include <iostream>
#include <limits.h>

using namespace std;

int main()
{
    cout << "Hello, World!" << endl;
    cout << "INT_MAX: " << INT_MAX << endl;
    cout << "CHAR_MAX: " << CHAR_MAX << endl;
    cout << "LONG_MAX: " << LONG_MAX << endl;

    return 0;
}

// -- Some useful limits to know (inside "limits.h"):

// char -> 1 byte
// CHAR_MAX = 127

// int -> 4 bytes
// INT_MAX = 2.147.483.647

// long -> 8 bytes
// LONG_MAX = 9.223.372.036.854.775.807