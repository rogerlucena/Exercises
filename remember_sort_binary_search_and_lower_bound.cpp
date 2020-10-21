// binary_search example
#include <iostream>     // std::cout
#include <algorithm>    // std::binary_search, std::sort
#include <vector>       // std::vector

#include "tools.cpp"

// bool myfunction (int i,int j) { return (i>j); } // the numbers satisfying this come first after the sort (default is <), works declaring myfunction this way
auto myfunction = [](int i,int j) { return (i>j); };

// Third paramater in sort(), lambda function as my comparator (do not forget "const ref"!!)
// auto cmp = [](const Interval &i1, const Interval &i2) -> bool {return i1.start < i2.start;};
// "-> bool" not necessary in lambda function

// Lower bound remember (in <algorithm>) - http://www.cplusplus.com/reference/algorithm/lower_bound/:
// Returns an iterator pointing to the first element in the range [first,last) which does not compare less 
// than val (>= val then, if multiple returns iterator to 1st one; iterator to last if not found).
// Unlike upper_bound (first in [first, last) that is > val, iterator to last if not found), the value 
// pointed by the iterator returned by lower_bound function may also be equivalent to val, and not only 
// greater (useful when wanting the position of binary_search).
// Note: the array must be sorted with comp, default is "<"
// template <class ForwardIterator, class T, class Compare>
//   ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);

// P.S.: upper_bound and lower_bound work the same way maps and sets too:
// but remember, for maps and sets we cannot do operations with the iterators such 
// as "m.upper_bound(n) - m.begin()", or "m.begin()+1" (bidirectional iterators do not allow it), only ++ or --

int rememberLowerBound() {
    vector<int> v{10, 20, 30, 30, 30, 40, 50}; 
    vector<int>::iterator low1, low2, low3; 
      
    // std :: lower_bound 
    low1 = lower_bound(v.begin(), v.end(), 30); 
    low2 = lower_bound(v.begin(), v.end(), 35); 
    low3 = lower_bound(v.begin(), v.end(), 55); 
  
    // Printing the lower bounds 
    cout << "lower_bound for element 30 at position : " << (low1 - v.begin()); // 2
    cout << "\nlower_bound for element 35 at position : " << (low2 - v.begin()); // 5
    cout << "\nlower_bound for element 55 at position : " << (low3 - v.begin()); // 7
    
    return 0;
}


int rememberSortAndBinarySearch() {
    int myints[] = {1,2,3,4,5,4,3,2,1};
    std::vector<int> v(myints,myints+9);  // 1 2 3 4 5 4 3 2 1

    // using default comparison:
    std::sort (v.begin(), v.end());

    std::cout << "looking for a 3... ";
    if (std::binary_search (v.begin(), v.end(), 3))
        std::cout << "found!\n"; else std::cout << "not found.\n";

    // using myfunction as comp:
    std::sort (v.begin(), v.end(), myfunction);
    // For pairs, if not specifying "smallerPair" it is going to take the .first and use the standard <
    // (for "Interval" or any other customized class you defined, you must provide the comparator function!)
    auto smallerPair = [](const pair<int, int> &p1, const pair<int, int> &p2) -> bool {return p1.first < p2.first;};

    cout << "Vector \"v\" sorted using myfunction: " << endl;
    printVector(v);  // 5, 4, 4, 3, 3, 2, 2, 1, 1

    std::cout << "looking for a 6... ";
    if (std::binary_search (v.begin(), v.end(), 6, myfunction))
        std::cout << "found!\n"; else std::cout << "not found.\n";

    return 0;
}

// looking for a 3... found!
// looking for a 6... not found.



// Binary Search - implementation:

// A recursive binary search function. It returns
// location of x in given array arr[l..r] is present,
// otherwise -1
int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) // "ele"=left, not one here
    {
        int mid = l + (r - l)/2; // "ele"=left and "erre"=right, not one here

        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid-1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid+1, r, x);
    }

    // We reach here when element is not
    // present in array
    return -1;
}
