#include <iostream>
#include <limits>

using namespace std;

// Complete list here: https://www.geeksforgeeks.org/c-data-types/
// int: 4 bytes, -2*10^9 to 2*10^9 (max is a bit more) 
// long: 8 bytes, -9*10^18 to 9*10^18 (max is a bit more)
// long long is at list as large as long, here we see that it is the same as long

int main() {
    cout << "Hello, World!" << endl;
    cout << "INT_MAX: " << INT_MAX << endl;
    cout << "CHAR_MAX: " << CHAR_MAX << endl;
    cout << "LONG_MAX: " << LONG_MAX << endl;
    cout << "LONG_LONG_MAX: " << __LONG_LONG_MAX__ << endl;
    return 0;
}

// -- Some useful limits to know (inside "limits.h"):

// char -> 1 byte
// CHAR_MAX = 127

// int -> 4 bytes
// INT_MAX =  2.147.483.647 (2^31-1)
// INT_MIN = -2.147.483.648 (-2^31)

// long -> 8 bytes
// LONG_MAX =  9.223.372.036.854.775.807 (2^63-1)
// LONG_MIN = -9.223.372.036.854.775.808 (-2^63)