#include <iostream>
#include <ctime>
#include <random>

using namespace std;

void shell_sort(int * arr, int size) {
    if (size <= 1) {
        return;
    }

    for (int h = size / 2; h > 0; h /= 2) {
        for (int i = h; i < size; i++) {
            int tmp = arr[i];
            int j = 0;

            for (j = i; j >= h && arr[j - h] > tmp; j -= h) {
                arr[j] = arr[j - h];
            }

            arr[j] = tmp;
        }
    }
}

int main() {
    srand(time(0));
    int size = 10;
    int * arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 101;
        cout << arr[i] << " ";
    }
    cout << endl;

    shell_sort(arr, 10);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}