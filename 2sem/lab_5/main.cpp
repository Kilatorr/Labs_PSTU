#include <iostream>

#define Size_a 4

using namespace std;

int scalar(int *a, int *b, int n) {
    int scal_prod = 0;

    for (int i = 0; i < n; i++) {
        scal_prod += a[i] * b[i];
    }
    return scal_prod;
}

bool is_orthonormal(int (*a)[Size_a], int n) {
    for (int i = 0; i < n; i++) {
        if (scalar(a[i], a[i], n) != 1) {
            return false;
        }

        for (int j = i + 1; j < n; j++) {

            if (scalar(a[i], a[j], n) != 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int arr[Size_a][Size_a] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
   
    if (is_orthonormal(arr, Size_a)) {
        cout << "Matix is orthonormal" << endl;
    }
    else {
        cout << "Matix is not orthonormal" << endl;
    }
    
    return 0;
}