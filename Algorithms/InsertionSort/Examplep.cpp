#include <iostream>
#include <vector>
using namespace std;

void insertsort(vector<int>& arr) {
    int n = arr.size();

    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

bool esPrimo(int numero) {
    if (numero == 0 || numero == 1 || numero == 4) return false;
    
    for (int x = 2; x <= numero / 2; x++) {
        if (numero % x == 0) return false;
    }

    return true;
}

void vectorPrimos(const vector<int>& numeros, vector<int>& primeNumbers) {
    for (int numero : numeros) {
        if (esPrimo(numero)) {
            primeNumbers.push_back(numero);
        }
    }
}

int main() {
    vector<int> numeros = {12, 5, 3, 7, 11, 4, 8, 13};
   
    insertsort(numeros);

    cout << "Sorted numbers: ";
    for(int i = 0; i < numeros.size(); i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    vector<int> primeNumbers;
    vectorPrimos(numeros, primeNumbers);

    cout << "Prime numbers: ";
    for(int i = 0; i < primeNumbers.size(); i++) {
        cout << primeNumbers[i] << " ";
    }
    cout << endl;

    return 0;
}
