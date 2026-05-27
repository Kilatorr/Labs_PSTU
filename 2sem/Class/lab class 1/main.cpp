#include "Point.h"
#include <iostream>
#include <clocale>
using namespace std;

Point make_point(double x, double y) {
    Point p;
    p.Init(x, y);
    return p;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Point p1;
    p1.Read();
    p1.Show();

    double x1, y1;
    cout << "Введите координаты второй точки: ";
    cin >> x1 >> y1;
    cout << "Расстояние между точками: " << p1.distance(x1, y1) << endl;

    Point* p2 = new Point;
    p2->Init(1.0, 2.0);
    p2->Show();
    delete p2;

    Point arr[2];
    for (int i = 0; i < 2; i++) {
        cout << "\nТочка " << i + 1 << ":\n";
        arr[i].Read();
    }
    for (int i = 0; i < 2; i++) {
        arr[i].Show();
    }

    Point* p_arr = new Point[2];
    for (int i = 0; i < 2; i++) {
        p_arr[i].Init(i * 1.0, i * 2.0);
        p_arr[i].Show();
    }
    delete[] p_arr;

    Point p3 = make_point(3.0, 4.0);
    p3.Show();

    return 0;
}