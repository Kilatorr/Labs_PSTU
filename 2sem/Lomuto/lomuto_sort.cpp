#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int lomutoSplit(int* arr, int low, int high) {
    int i = low - 1;
    int pivot = arr[high];

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return (i + 1);
}

void lomutoSort(int* arr, int low, int high) {
    if (low < high) {
        int pivot_index = lomutoSplit(arr, low, high);
        lomutoSort(arr, low, pivot_index - 1);
        lomutoSort(arr, pivot_index + 1, high);
    }
}

int main() {
    srand(time(0));
    int size = 10;
    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
        cout << arr[i] << " ";
    }
    cout << endl;

    lomutoSort(arr, 0, size - 1);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}