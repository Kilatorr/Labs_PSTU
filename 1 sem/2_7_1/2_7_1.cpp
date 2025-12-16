#include <iostream>
#include <math.h>

using namespace std;

int main() {
    int n;

    cin >> n;

    int a = sqrt(n);

    if (a * a == n && n >= 4) {
        for (int i = 1; i <= a; i++) {
            for (int j = 1; j <= a; j++) {
                cout << "*";
            }
            cout << endl;
        }
    }
    else if (n < 4) {
        cout << "Невозможно создать квадрат, так как N < 4" << endl;
    }
    else {
        cout << "Невозможно создать квадрат, содержащий N точек" << endl;
    }

    return 0;
}