#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double first;
    double second;

public:
    void Init(double x, double y);
    void Read();
    void Show();
    double distance(double x1, double y1);
};