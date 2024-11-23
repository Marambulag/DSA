/*#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Bank {

public:

void addAccount(string accountNumber, double initialBalance);
double getBalance(string, accountNumber);
double addBalance(string accountNumber, double balance);

private:

struct BankAccount{
    string accountNumber;
    double balance;
};

vector<BankAccount> accounts;
int findAccountIndex(string accountNumber);


}*/

#ifndef BANK_HPP
#define BANK_HPP

#include <iostream>
#include <vector>
#include <string>

class Bank {
public:
    void addAccount(std::string accountNumber, double initialBalance);
    double getBalance(std::string accountNumber);
    double addBalance(std::string accountNumber, double balance);
    double restBalance(std::string accountNumber, double balance);
private:
    struct BankAccount {
        std::string accountNumber;
        double balance;
    };

    
    std::vector<BankAccount> accounts;
    int findAccountIndex(std::string accountNumber);
};

#endif
