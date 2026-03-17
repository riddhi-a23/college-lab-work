#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    double balance;
    
    static int accountCount; 

public:
    BankAccount(int accNum, string name, double initialBalance) {
        accountNumber = accNum;
        accountHolderName = name;
        balance = initialBalance;
        accountCount++;
    }

    ~BankAccount() {
        accountCount--;
    }

    friend class BankManager;
};

int BankAccount::accountCount = 0;

class BankManager {
public:
    int countAccounts() const {
        return BankAccount::accountCount;
    }

    void displayAccountDetails(const BankAccount& acc) const {
        cout << "--- Account Details ---" << endl;
        cout << "Account Number: " << acc.accountNumber << endl;
        cout << "Account Holder: " << acc.accountHolderName << endl;
        cout << "Balance: $" << acc.balance << endl;
        cout << "-----------------------" << endl;
    }

    bool checkSufficientBalance(const BankAccount& acc, double amount) const {
        return acc.balance >= amount;
    }

    // iii. Transfer money between two accounts
    void transferMoney(BankAccount& fromAccount, BankAccount& toAccount, double amount) {
        cout << "\nAttempting to transfer $" << amount << " from " 
             << fromAccount.accountHolderName << " to " << toAccount.accountHolderName << "..." << endl;
             
        if (checkSufficientBalance(fromAccount, amount)) {
            fromAccount.balance -= amount;
            toAccount.balance += amount;
            cout << "Transaction Successful!" << endl;
        } else {
            cout << "Transaction Failed: Insufficient funds in " << fromAccount.accountHolderName << "'s account." << endl;
        }
    }
};

int main() {
    BankManager manager;

    BankAccount acc1(1001, "Alice Smith", 500.00);
    BankAccount acc2(1002, "Bob Jones", 300.00);

    cout << "Total Active Bank Accounts: " << manager.countAccounts() << "\n\n";

    manager.displayAccountDetails(acc1);
    manager.displayAccountDetails(acc2);

    cout << "\nChecking if Alice has at least $100: ";
    if (manager.checkSufficientBalance(acc1, 100.0)) {
        cout << "Yes.\n";
    } else {
        cout << "No.\n";
    }

    manager.transferMoney(acc1, acc2, 200.00);
    
    cout << "\nDetails after first transfer:" << endl;
    manager.displayAccountDetails(acc1);
    manager.displayAccountDetails(acc2);

    manager.transferMoney(acc1, acc2, 1000.00);

    return 0;
}