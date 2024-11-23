#include <iostream>
#include <vector>
#include <string>
using namespace std;

void bubblesort(vector<int>& vec) {
    int n = vec.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            if(vec[j] > vec[j + 1]) {
                int temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
        }
    }
}

int main() {
    vector<int> vec = {85, 70, 95, 60, 90};

    bubblesort(vec);

    for(int num : vec) {
        cout << num << " ";
    }

    return 0;
}