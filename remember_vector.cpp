// constructing vectors
#include <iostream>
#include <vector>

using namespace std;

// has push_back and pop_back
// to take a subvector only creating a new vector and using pointers to the wanted positions
// vector<int> new_v (old_vector.begin()+10, old_vector.end()-5)

// v.clear() -> makes the vector an empty vector again (do not confuse with setting all the values to zero)

// Initialize a matrix (with -1 everywhere):
// vector<vector<int>> m (len1, vector<int>(len2, -1));

// The line below is really making a copy of vec1 into vec2 !! 
// vector<int> vect2; vec2 = vec1;
int main ()
{
    // Initializing vector with values 
    vector<int> vect1{1, 2, 3, 4}; 
  
    // Declaring new vector 
    vector<int> vect2; 
  
    // Using assignment operator to copy one 
    // vector to other 
    vect2 = vect1; 


    // constructors used in the same order as described above:
    std::vector<int> first;                                // empty vector of ints
    std::vector<int> second (4,100);                       // four ints with value 100
    std::vector<int> third (second.begin(),second.end());  // iterating through second
    std::vector<int> fourth (third);                       // a copy of third

    // reserve
    std::vector<int> newSecond; 
	newSecond.reserve(second.size());

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

    std::cout << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    // Inserting:
    std::vector<int> myvector (3,100);
    std::vector<int>::iterator it;
    it = myvector.begin();
    it = myvector.insert ( it , 200 );
    myvector.insert (it,2,300); // 300, 300, 200, 100, 100, 100

    for(int i: myvector) cout << i << endl;

    return 0;
}