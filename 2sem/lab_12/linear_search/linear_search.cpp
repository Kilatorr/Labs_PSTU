#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int linear_search(int * arr, int size, int elem) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == elem) {
            return i;
        }
    }
    return -1;
}

int main() {
    srand(time(0));
    int size = 10;
    int * arr = new int[10];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
        cout << arr[i] << " ";
    }
    cout << endl;

    int idx = linear_search(arr, size, 5);

    if (idx == -1) {
        cout << "Elem not found" << endl;
    }
    else {
        cout << "Elem found, index: " << idx << endl;
    }
    
    delete[] arr;

    return 0;
}