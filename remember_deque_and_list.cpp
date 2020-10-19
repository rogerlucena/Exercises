#include <iostream>
#include <vector>

using namespace std;

// -- Difference between "list" and "deque"
// "deque" uses a dynamic array, "list" is a doubly linked list
// "deque" provides random acess and has almost same interface as a vector
// "list" fast insertion and deletion in any position, "deque" only in end/beginning (middle is linear)
// "deque" with insert or delete in any position other than end/beginning invalidates all pointers/iterators/references 
//     to elements of it, differently than "list", see lru_cache problem
// https://stackoverflow.com/questions/1436020/whats-the-difference-between-deque-and-list-stl-containers



// Deque (in #include <queue>, erase invalidates the pointers to node, see lru_cache)
// front(), back(), at() (reference to the element there), push_back(), push_front(), void pop_back(), void pop_front()
// iterator insert (iterator position, const value_type& val);
// void insert     (iterator position, size_type n, const value_type& val) // n repetitions of val
// void insert     (iterator position, InputIterator first, InputIterator last)
// add just before "position" and return an "it" to the first of the newly added elements (first case)
// (same thing with std::list)



// std::list -> is a doubly linked list (can operate with pointers, different than deque - see lru_cache problem)
// .front(), .back(), .clear(), push_back, push_front, pop_back, pop_front
//      void remove (const value_type& val); -> remove elemnts with that value
//      iterator erase (iterator position);
//      iterator erase (iterator first, iterator last);
//          erase return an iterator to the the element that followed the last element erased by the function call             
//      iterator insert (iterator position, const value_type& val);
//      void insert     (iterator position, size_type n, const value_type& val) // n repetitions of val
//      void insert     (iterator position, InputIterator first, InputIterator last)
//          add just before "position" and return an "it" to the first of the newly added elements (first case)
//          (same thing with std::deques)

int main() {
	cout << "Hello, World!";
	return 0;
}