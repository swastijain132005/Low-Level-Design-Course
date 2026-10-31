#include <iostream>
using namespace std;

class Account {
public:
    virtual void deposit(int amount) = 0;
};

class WithdrawableAccount : public Account {
public:
    virtual void withdraw(int amount) = 0;
};

class SavingsAccount : public WithdrawableAccount {
public:
    void deposit(int amount) override {
        cout << "Savings: Deposit " << amount << endl;
    }

    void withdraw(int amount) override {
        cout << "Savings: Withdraw " << amount << endl;
    }
};

class FixedDepositAccount : public Account {
public:
    void deposit(int amount) override {
        cout << "Fixed Deposit: Deposit " << amount << endl;
    }
};

// Only accounts supporting withdrawal are passed here
void processWithdrawal(WithdrawableAccount* acc) {
    acc->withdraw(500);
}

int main() {

    SavingsAccount s;
    FixedDepositAccount f;

    s.deposit(1000);
    f.deposit(1000);

    processWithdrawal(&s);

    // processWithdrawal(&f); // Not allowed!

    return 0;
}
