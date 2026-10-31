//Liskov Substitution Principle (LSP)
//LSP is the L in SOLID principles.

//It states: Objects of a parent class should be replaceable with objects of its child classes without changing the correctness of the program.

//in simple words:If class B inherits from class A, then wherever we use an object of A, we should be able to use an object of B without breaking the functionality.

//A Fixed Deposit Account allows deposits but does not allow withdrawals. So it should not be forced to inherit an interface that requires withdrawal.


#include <iostream>
using namespace std;

class Account {
public:
    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
};

class SavingsAccount : public Account {
public:
    void deposit(int amount) override {
        cout << "Deposited " << amount << endl;
    }

    void withdraw(int amount) override {
        cout << "Withdrawn " << amount << endl;
    }
};

class FixedDepositAccount : public Account {
public:
    void deposit(int amount) override {
        cout << "Deposited " << amount << endl;
    }

    void withdraw(int amount) override {
        cout << "Withdrawal not allowed!" << endl;
    }
};

void processAccount(Account* acc) {
    acc->deposit(1000);
    acc->withdraw(500);
}

int main() {
    SavingsAccount s;
    FixedDepositAccount f;

    processAccount(&s); // Works
    processAccount(&f); // Doesn't support expected withdrawal
}
