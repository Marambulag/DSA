/*#inculde "bank.hpp"
using namespace std;

void Bank::addAccount(string accountNumber, double initialBalance) {
    accounts.push_back({accountNumber, initialBalance});

}
 
int Bank::addBalance(string accountNumber, double balance){
    int index = findAccountIndex(accountNumber);
    if(index != -1){
        return accounts[index].balance =  accounts[index].balance + balance;
    }
    return-1;
}
    


double Bank::getBalance(string accountNumber){
    int index = findAccountIndex(accountNumber);
    if(index != -1){
        return accounts[index].balance;
    }
    return-1;
}



 int Bank:: findAccountIndex(string accountNumber){
  for(size_t i = 0; i < accounts.size(); i++){
        if (accounts[i].accountNumber  == accountNumber) {
            return i;
        }
    }
    return -1;
}*/

#include "bank.hpp"

void Bank::addAccount(std::string accountNumber, double initialBalance) {
    accounts.push_back({accountNumber, initialBalance});
}




double Bank::getBalance(std::string accountNumber) {
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        return accounts[index].balance;
    }
    return -1;
}

double Bank::addBalance(std::string accountNumber, double balance) {
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        accounts[index].balance += balance;
        return accounts[index].balance;
    }
    return -1;
}

double Bank::restBalance(std::string accountNumber, double balance) {
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        accounts[index].balance -= balance;
        return accounts[index].balance;
    }
    return -1;
}


int Bank::findAccountIndex(std::string accountNumber) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}