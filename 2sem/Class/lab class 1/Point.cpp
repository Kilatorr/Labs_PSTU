#include "Point.h"
#include <iostream>
#include <cmath>
using namespace std;

void Point::Init(double x, double y) {
    first = x;
    second = y;
}

void Point::Read() {
    cout << "Введите координату x: ";
    cin >> first;
    cout << "Введите координату y: ";
    cin >> second;
}

void Point::Show() {
    cout << "Точка (" << first << "; " << second << ")" << endl;
}

double Point::distance(double x1, double y1) {
    return sqrt((first - x1)*(first - x1) + (second - y1)*(second - y1));
}