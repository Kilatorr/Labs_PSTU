#include <iostream>

using namespace std;

int main() {
    int n;

    cin >> n;

    if (n > 2) {

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                cout << "* ";
            }

            cout << endl;
        }
    }
    else {
        cout << "Невозможно построить треугольник, так как N < 2" << endl;
    }

    return 0;
}