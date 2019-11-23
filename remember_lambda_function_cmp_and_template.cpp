#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// How to receives a Lambda function as parameter in C++
template<class T>
void printVector(const vector<T> &v, function<void(const T&)>  printEl) {
	for(int i = 0; i < v.size(); i++) {
		printEl(v[i]);
		if(i < v.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

// Definition for an interval.
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

bool myfunction (int i,int j) { return (i>j); } // the numbers satisfying this come first after the sort (default is <)

int main() {
	// intervals: [1,3],[2,6],[8,10],[15,18]
	Interval i1 = {1, 3};
	Interval i2 = {2, 6};
	Interval i3 = {8, 10};
	Interval i4 = {15, 18};

	vector<Interval> intervals = {i1, i2, i3, i4};

    // Lambda function in C++
	auto printEl = [](const Interval &i) -> void {cout << "[" << i.start << "," << i.end << "]";};
	auto x1 = [](int i) { return i; }; // without the arrow also works
	printVector(intervals, (function<void(const Interval&)>) printEl); // passing a Lambda function as parameter


    // -------------------------------
    int myints[] = {1,2,3,4,5,4,3,2,1};
    std::vector<int> v(myints,myints+9);

    // Using a Lambda function as cmp to sort:
    // (using myfunction as comp)
    sort (v.begin(), v.end(), myfunction);
    cout << "Vector \"v\" sorted using myfunction: " << endl;
    for(int el : v) {
        cout << el << " ";  // 5 4 4 3 3 2 2 1 1
    }

	return 0;
}