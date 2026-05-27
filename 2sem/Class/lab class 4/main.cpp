#include "Time.h"
#include <iostream>
#include <clocale>
using namespace std;

void f1(Triad& t) {
    t.setFirst(10);
    t.setSecond(30);
    t.setThird(45);
    cout << t << endl;
}

Triad f2() {
    Time t(23, 59, 59);
    return t;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Triad tr1;
    cin >> tr1;
    cout << tr1 << endl;

    Time t1, t2;
    cin >> t1;
    cin >> t2;

    cout << t1 << endl;
    cout << t2 << endl;

    if (t1 == t2) cout << "Равны" << endl;
    if (t1 != t2) cout << "Не равны" << endl;
    if (t1 < t2)  cout << t1 << " раньше " << t2 << endl;
    if (t1 > t2)  cout << t1 << " позже " << t2 << endl;
    if (t1 <= t2) cout << t1 << " <= " << t2 << endl;
    if (t1 >= t2) cout << t1 << " >= " << t2 << endl;

    f1(t1);

    Triad tr2 = f2();
    cout << tr2 << endl;

    return 0;
}