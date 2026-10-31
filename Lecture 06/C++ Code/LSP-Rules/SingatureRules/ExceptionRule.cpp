

#include <iostream>

using namespace std;

// Exception Rule:
// A subclass should throw fewer or narrower exceptions 
// (but not additional or broader exceptions) than the parent.
// C++ does not enforces this. Hence no compilation error.

/*
├── std::logic_error        <-- For logical errors detected before runtime
│   ├── std::invalid_argument   <-- Invalid function argument
│   ├── std::domain_error       <-- Function argument domain error
│   ├── std::length_error       <-- Exceeding valid length limits
│   ├── std::out_of_range       <-- Array or container index out of bounds
│
├── std::runtime_error      <-- For errors that occur at runtime
│   ├── std::range_error        <-- Numeric result out of range
│   ├── std::overflow_error     <-- Arithmetic overflow
│   ├── std::underflow_error   
*/

#include <iostream>
#include <stdexcept>
using namespace std;

class Parent {
public:
    virtual void getValue() {
        throw logic_error("Parent error");
    }
};

class Child : public Parent {
public:
    void getValue() override {
        throw out_of_range("Child error");
    }
};

int main() {
    Parent p;
    Child c;

    Parent* obj = &p;

    try {
        obj->getValue();
    }
    catch (const logic_error& e) {
        cout << e.what() << endl;
    }

    obj = &c;

    try {
        obj->getValue();
    }
    catch (const logic_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
