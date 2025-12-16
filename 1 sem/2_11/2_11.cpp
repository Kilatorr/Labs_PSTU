#include <iostream>

using namespace std;

int main() {
    int n, a;
    bool plus_flag = false;
    bool minus_flag = false;

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a;

        if (a == 0) {
            continue;
        }
        else if (a > 0 && plus_flag != true && minus_flag != true) {
            plus_flag = true;
        }
        else if (a < 0 && plus_flag != true && minus_flag != true) {
            minus_flag = true;
        }
    }

    if (plus_flag == true) {
        cout << "Plus" << endl;
    }
    else if (minus_flag == true) {
        cout << "Minus" << endl;
    }
    else {
        cout << "0" << endl;
    }

    return 0;
}