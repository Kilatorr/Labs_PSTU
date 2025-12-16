#include <iostream>

using namespace std;

int main() {
    int n;

    cin >> n;


    if (n >= 3) {
        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= n; j++) {
                
                if (i == 1 || i == n || j == 1 || j == n) {
                  cout << "* ";  
                }
                else {
                    cout << "  ";
                }
            } 
        cout << endl; 
        }
    }
    else {
        cout << "Невозможно создать квадрат, так как N < 3" << endl;
    }

    return 0;
}