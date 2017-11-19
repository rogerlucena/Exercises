#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*

 -- Problem Statement:

 Rebuild queue

 "n" people were waiting on a line to buy a cinema ticket. Each person knew how many
 people taller than him/her were in front of him/her. But they did not know their exact
 position.

 A fire alarm sounds and all people leave the queue. Since it was just a false alarm,
 they wanna build the line back in the exact same configuration it was before.

 class QueuedPerson{
    int h; // height in inches
    int t; // Number of taller people if front of him/her
 };

 INPUT: vector<QueuedPerson> people
 OUTPUT: The heights printed in the original order

 Example below:

 The orignal line was:
 {(begin) {h:4, t:2}, {h:6, t:0}, {h:3, t:1}, {h:5, t:0} (end)}

 The input is a suffle of the vector of QueuedPerson above
 Right output shall be: 4 6 3 5

*/

class QueuedPerson {
    public:
     int h_; // height
     int t_; // number of taller people in front of this one

     QueuedPerson(int h, int t) : h_(h), t_(t) {}

     bool operator < (const QueuedPerson &b) const {
         return this->h_ < b.h_;
     }
};

void swap(vector<QueuedPerson> &people, int p1, int p2) {
    auto aux = people[p1];
    people[p1] = people[p2];
    people[p2] = aux;
}

void advance(vector<QueuedPerson> &people, int pos, int steps) {
    int j=0;
    while(steps >= 1) {
        swap(people, pos+j, pos+1+j);
        ++j;
        --steps;
    }
}

int main()
{
    vector<QueuedPerson> people = {QueuedPerson(3, 1), QueuedPerson(6, 0), QueuedPerson(5, 0), QueuedPerson(4, 2)};
    sort(people.begin(), people.end());

    // Sorted by the height - printing to verify correctness:
    /*
    for(QueuedPerson p : people) {
        cout << p.h_ << endl;
    }
    cout << "----------" << endl;
    */

    int size = people.size();
    for(int i = size-1; i>=0; --i) {
        advance(people, i, (size-1-i)-people[i].t_);
    }

    // Printing the final order of heights:
    cout << "The original order of heights was: " << endl;
    for(QueuedPerson p : people) {
        cout << p.h_ << " ";
    }

    return 0;
}