#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<int> &leftArray, vector<int> &rightArray, vector<int> &array) {

    int leftSize = leftArray.size();
    int rightSize = rightArray.size();

    // Indices
    int i = 0;
    int l = 0;
    int r = 0;

    // Main loop
    while( l < leftSize && r < rightSize) {
        if(leftArray[l] < rightArray[r]) {
            array[i] = leftArray[l];
            i++;
            l++;
        } else {
            array[i] = rightArray[r];
            i++;
            r++;
        }
    }

    while (l < leftSize) {
        array[i] = leftArray[l];
        i++;
        l++;
    }

    while (r < rightSize) {
        array[i] = rightArray[r];
        i++;
        r++;
    }

}

void MergeSort(vector<int> &array) {

    int n = array.size();
    if( n <= 1) return; // Base case
    int center = n / 2;
    // Crear arreglo izquierdo y derecho con el size de center y n - center
    vector<int> leftArray(center);
    vector<int> rightArray(n - center);

    for( int i = 0; i < n; i++) {
        if (i < center) {
            leftArray[i] = array[i];
        } else {
            rightArray[i - center] = array[i];
        }
    }
    
    // Divide
    MergeSort(leftArray);
    MergeSort(rightArray);

    // Conquer
    Merge(leftArray, rightArray, array);

}

int main() {

    vector<int> array = {12, 3, 7, 9, 14, 6, 11, 2};

    
    MergeSort(array);

    for( int num: array) {
        cout << num << " ";
    }
    
    return 0;
}