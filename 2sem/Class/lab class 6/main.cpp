#include <clocale>
#include <iostream>

#include "Set.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");

    Set a(5);
    cout << "Vvedite elementi mnozhestva a:" << endl;
    cin >> a;
    cout << "a = " << a << endl;

    cout << "Razmer mnozhestva a = " << a() << endl;
    cout << "a[2] = " << a[2] << endl;

    a[2] = 100;
    cout << "Posle izmenenia a[2]:" << endl;
    cout << "a = " << a << endl;

    Set b(3);
    cout << endl << "Vvedite elementi mnozhestva b:" << endl;
    cin >> b;
    cout << "b = " << b << endl;

    Set c;
    c = a + b;
    cout << endl << "Obedinenie mnozhestv a i b:" << endl;
    cout << "c = " << c << endl;

    Set d = c;
    cout << endl << "Constructor copirovania:" << endl;
    cout << "d = " << d << endl;

    cout << endl << "Perebor mnozhestva c s pomoshyu iteratora:" << endl;
    Iterator i;
    for (i = c.first(); i != c.last(); i++) {
        cout << *i << " ";
    }
    cout << endl;

    cout << endl << "Perehod k sleduyushemu elementu cherez ++:" << endl;
    i = c.first();
    cout << *i << endl;
    ++i;
    cout << *i << endl;

    return 0;
}
