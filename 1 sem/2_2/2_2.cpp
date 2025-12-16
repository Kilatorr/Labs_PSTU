#include <iostream>

using namespace std;

int main() {
    int n;
    int proizv = 1;

    cin >> n;

    if (n <= 0) {
        cout << "Невозможно посчитать произведение N натуральных чисел при N <= 0" << endl;
    }
    else {
        for (int i = 1; i <= n; i++) {
            proizv *= i;
        }
        
        cout << proizv << endl;
    }
    
    return 0;
}