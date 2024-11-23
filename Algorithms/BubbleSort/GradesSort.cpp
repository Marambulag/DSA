#include <iostream>
#include <vector>
using namespace std;

void mswap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}
void bubblesort(vector<int>& vec) {
    int n = vec.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            if(vec[j] > vec[j + 1]) {
             swap(vec[j], vec[j + 1]);
            }
        }
    }
}


int main() {
    vector<int> vec(7);
    cout << "Ingresa 7 calificaciones: " << endl;
    
    for(int i = 0; i < 7; ++i) {
        cin >> vec[i]; 
    }

    bubblesort(vec);

    cout << "Calificaciones ordenadas: ";
    for(int num : vec) {
        cout << num << " ";
    }
    

    cout << "Calificación más baja: " << vec[0] << endl;
    cout << "Calificación más alta: " << vec[6] << endl;

    return 0;
}
