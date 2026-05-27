#include "Vector.h"
#include "Triad.h"
#include "Time.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Vector v(4);

    Triad* tr1 = new Triad(1, 2, 3);
    Time*  t1  = new Time(10, 30, 0);
    Triad* tr2 = new Triad(4, 5, 6);
    Time*  t2  = new Time(22, 15, 45);

    v.Add(tr1);
    v.Add(t1);
    v.Add(tr2);
    v.Add(t2);

    cout << v;

    delete tr1;
    delete t1;
    delete tr2;
    delete t2;

    return 0;
}
