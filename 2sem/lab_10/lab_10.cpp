#include <iostream>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    int rows, cols;

    cout << "Enter rows cols: ";
    cin >> rows >> cols;
    cout << endl;

    int ** arr = new int* [rows];

    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = rand() % 10;
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int line_num;

    cout << "Enter num of line: ";
    cin >> line_num;
    cout << endl;

    delete[] arr[line_num - 1];
    rows--;

    for (int i = line_num - 1; i < rows; i++) {
        arr[i] = arr[i + 1];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        delete[] arr[i];
        cout << endl;
    }
    cout << endl;

    delete[] arr;

    return 0;
}