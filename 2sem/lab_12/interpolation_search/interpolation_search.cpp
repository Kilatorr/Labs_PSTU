#include <iostream>
#include <ctime>
#include <random>

using namespace std;

int interpolation_search(int * arr, int size, int elem) {
    int low = 0;
    int high = size - 1;

    while (arr[low] <= elem && elem <= arr[high] && low <= high) {
        if ((low == high) || (arr[low] == arr[high])) {
            if (arr[low] == elem) {
                return low;
            }
            else {
                return -1;
            }
        }
        
        int pos = low + ((elem - arr[low]) * (high - low)) / (arr[high] - arr[low]);

        if (arr[pos] == elem) {
            return pos;
        }
        else if (elem > arr[pos]) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }
    return -1;
}

void sort(int * arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    srand(time(0));
    int size = 10;
    int * arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    sort(arr, size);

    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int idx = interpolation_search(arr, size, 23);

    if (idx == -1) {
        cout << "Elem not found" << endl;
    }
    else {
        cout << "Elem found, index: " << idx << endl;
    }

    delete[] arr;

    return 0;
}