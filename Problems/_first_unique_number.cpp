#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// https://leetcode.com/explore/other/card/30-day-leetcoding-challenge/531/week-4/3313/
// Think simple: invariant

// You have a queue of integers, you need to retrieve the first unique integer in the queue.

// Implement the FirstUnique class:

// FirstUnique(int[] nums) Initializes the object with the numbers in the queue.
// int showFirstUnique() returns the value of the first unique integer of the queue, and returns -1 
// if there is no such integer.
// void add(int value) insert value to the queue.
 
// Example:

// Input: 
// ["FirstUnique","showFirstUnique","add","showFirstUnique","add","showFirstUnique","add","showFirstUnique"]
// [[[2,3,5]],[],[5],[],[2],[],[3],[]]
// Output: 
// [null,2,null,2,null,3,null,-1]

// Explanation: 
// FirstUnique firstUnique = new FirstUnique([2,3,5]);
// firstUnique.showFirstUnique(); // return 2
// firstUnique.add(5);            // the queue is now [2,3,5,5]
// firstUnique.showFirstUnique(); // return 2
// firstUnique.add(2);            // the queue is now [2,3,5,5,2]
// firstUnique.showFirstUnique(); // return 3
// firstUnique.add(3);            // the queue is now [2,3,5,5,2,3]
// firstUnique.showFirstUnique(); // return -1

class FirstUnique {
     queue<int> q;
     unordered_map<int,int> m;

public:
    FirstUnique(vector<int> &nums) {
        for(int n : nums){
             q.push(n);
             m[n]++;
        }
    }
    
    int showFirstUnique() {
        while(!q.empty() && m[q.front()] > 1) {
            q.pop();
		}
        
        if(q.empty()) {
             return -1;
		}

        return q.front();
    }
    
    void add(int value) {
        q.push(value);
        m[value]++;
    }
};

int main() {
	unordered_map<int,int> m;
	m[2]++; // default value seems to be 0
	cout << "v: " << m[2] << endl; // 1

	return 0;
}