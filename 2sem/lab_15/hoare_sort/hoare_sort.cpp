#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int hoare_split(int * arr, int low, int high) {
    int pivot = arr[(high + low) / 2];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        }
        while(arr[i] < pivot);

        do {
            j--;
        }
        while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }
        swap(arr[i], arr[j]);
     }
}

void hoare_sort(int * arr, int low, int high) {
    if (low < high) {
        int p_idx = hoare_split(arr, low, high);
        hoare_sort(arr, low, p_idx);
        hoare_sort(arr, p_idx + 1, high);
    }
}

int main() {
    srand(time(0));
    int size = 10;
    int * arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
        cout << arr[i] << " ";
    }
    cout << endl;

    hoare_sort(arr, 0, size - 1);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}