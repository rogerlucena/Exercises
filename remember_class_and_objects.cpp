#include <iostream>
#include <vector>

using namespace std; 

// Obs: public and private keywords use half of the normal tab space (from Google C++ guide).

// - Interfaces, abstract classes and virtual methods
// Pure virtal methods are methods with no implementation, you put "virtual void f() = 0;"
//      classes with virtual methods cannot be instantiated
// Abstract classes are classes with at least one virtual method, others may be implemented
// Interfaces can be understood as pure virtual classes (all methods are virtual, no implementations)

// - Explaining public, protected and private
// https://www.geeksforgeeks.org/inheritance-in-c/
// Identation: half of the normal tab space
class A { // default in classes is private, in structs is public
  public:
    int x; 
  protected:
    int y; 
  private:
    int z; 
}; 
  
class B : public A {
    // x is public 
    // y is protected 
    // z is not accessible from B 
}; 
  
class C : protected A {
    // x is protected 
    // y is protected 
    // z is not accessible from C 
}; 
  
class D : private A { // 'private' is default for classes 
    // x is private 
    // y is private 
    // z is not accessible from D 
}; 


// - Example of multilevel inheritance:

// base class 
class Vehicle {
  public: 
    Vehicle() { 
      cout << "This is a Vehicle" << endl; 
    } 
}; 

class fourWheeler: public Vehicle {
  public: 
    fourWheeler() { 
      cout<<"Objects with 4 wheels are vehicles"<<endl; 
    } 
}; 

// sub class derived from two base classes 
class Car: public fourWheeler{
   public: 
     Car() { 
       cout<<"Car has 4 Wheels"<<endl; 
     } 
}; 
  
// main function 
int main() {
    //creating object of sub class will 
    //invoke the constructor of base classes 
    Car obj; 
    return 0; 
}

// Output:
// This is a Vehicle
// Objects with 4 wheels are vehicles
// Car has 4 Wheels



// - Example of multiple inheritance:

// first base class 
class Vehicle {
  public: 
    Vehicle() { 
      cout << "This is a Vehicle" << endl; 
    } 
}; 
  
// second base class 
class FourWheeler {
  public: 
    FourWheeler() { 
      cout << "This is a 4 wheeler Vehicle" << endl; 
    } 
}; 
  
// sub class derived from two base classes 
class Car: public Vehicle, public FourWheeler {
  
}; 

int main2() {
	// creating object of sub class will 
    // invoke the constructor of base classes 
    Car obj;
	return 0;
}

// Output:
// This is a Vehicle
// This is a 4 wheeler Vehicle