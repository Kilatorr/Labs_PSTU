#include <iostream>
using namespace std;

void hanoi(int n, int start, int to, int k) {
    if (n == 1) {
        cout << "переместить 1 диск с " << start << " на " << to << endl;
        return;
    }

    hanoi(n - 1, start, k, to);
    cout << "Переметить " << n << " с " << start << " на " << to << endl;
    hanoi(n - 1, k, to, start);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int disks;
    cin >> disks;
    cout << "Используется " << disks << " диск(ов)" << endl << endl;
    hanoi(disks, 1, 3, 2); 

    return 0;
}
