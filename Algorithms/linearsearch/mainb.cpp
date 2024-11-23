/*#include <iostream>
#include "bank.hpp"
using namespace std;

/*int main()

{
    Bank bank;

    bank.addAccount("aa12", initialBalance: 150);
    cout << "El balance de tu cuenta aa12 es: " << bank.getBalance(accountNumber "aa12") << endl;
   
   
    cout << "Ingresa numero de cuenta: " <<endl;
    cin >> accountNumber;
   
    cout << "Ingresa balance que quieras agragar a cuenta: " <<endl;
    cin >> balance;
    
    Balance = initialBalance + balance;

    bank.addBalance(accountNumber, Balance);
    

    
    return 0;
};*/

#include <iostream>
#include "bank.hpp"

int main() {
    Bank bank;
    std::string accountNumber;
    double initialBalance;
    double balance;

    std::cout << "Ingresa numero de cuenta: " << std::endl;
    std::cin >> accountNumber;

    std::cout << "Ingresa Balance inicial: " << std::endl;
    std::cin >> initialBalance;


    bank.addAccount(accountNumber, initialBalance);
    std::cout << "Numero cuenta: " << accountNumber << std::endl << "Balance inicial " << bank.getBalance(accountNumber) << std::endl;

    std::cout << "Ingresa numero de cuenta: " << std::endl;
    std::cin >> accountNumber;

    std::cout << "Ingresa balance que quieras agregar a cuenta: " << std::endl;
    std::cin >> balance;

    bank.addBalance(accountNumber, balance);

    std::cout << "El nuevo balance de tu cuenta " << accountNumber << " es: " << bank.getBalance(accountNumber) << std::endl;

    std::cout << "Ingresa balance que quieras restar a cuenta: " << std::endl;
    std::cin >> balance;

    bank.restBalance(accountNumber, balance);

    std::cout << "El nuevo balance de tu cuenta " << accountNumber << " es: " << bank.getBalance(accountNumber) << std::endl;

    return 0;
}
