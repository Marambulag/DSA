#include <iostream>
#include <vector>


using namespace std;


int linearsearch(vector<int> vec, int target){
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] > target) {
            return i;
        }
    }

    return -1;

}

    int main(){

    vector<int> vec = {5, 2, 9, 7, 4, 6};
    int target = 5;


   int index = linearsearch(vec, target);

    if(index != -1){
        cout<<"elemento encontrado: "<<index<<endl;
    }

    return 0;
}
