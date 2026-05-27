#include "Money.h"
#include "Container.h"
#include "Set.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "Zadacha 1. Associativnyi container multimap<int, double>" << endl;
    Container<double> a;
    a.Add(0, 2.5);
    a.Add(1, 7.4);
    a.Add(2, 1.2);
    a.Add(3, 4.8);
    cout << "Nachalnyi container:" << endl;
    a.Print();
    a.MaxAddBegin();
    cout << "Posle dobavleniya max v nachalo:" << endl;
    a.Print();
    a.DelMin();
    cout << "Posle udaleniya min:" << endl;
    a.Print();
    a.AddAverage();
    cout << "Posle dobavleniya srednego:" << endl;
    a.Print();

    cout << endl << "Zadacha 2. Associativnyi container multimap<int, Money>" << endl;
    Container<Money> b;
    b.Add(0, Money(10, 50));
    b.Add(1, Money(7, 25));
    b.Add(2, Money(15, 10));
    b.Add(3, Money(3, 40));
    cout << "Nachalnyi container:" << endl;
    b.Print();
    b.MaxAddBegin();
    cout << "Posle dobavleniya max v nachalo:" << endl;
    b.Print();
    b.DelMin();
    cout << "Posle udaleniya min:" << endl;
    b.Print();
    b.AddAverage();
    cout << "Posle dobavleniya srednego:" << endl;
    b.Print();

    cout << endl << "Zadacha 3. Parametrizovannyi klass Set<Money>" << endl;
    Set<Money> c;
    c.Add(Money(5, 20));
    c.Add(Money(11, 30));
    c.Add(Money(4, 90));
    cout << "Nachalnoe mnozhestvo: ";
    c.Print();
    c.MaxAddBegin();
    cout << "Posle dobavleniya max v nachalo: ";
    c.Print();
    c.DelMin();
    cout << "Posle udaleniya min: ";
    c.Print();
    c.AddAverage();
    cout << "Posle dobavleniya srednego: ";
    c.Print();

    return 0;
}
