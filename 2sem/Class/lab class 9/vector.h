#pragma once
#include <iostream>
#include "Error.h"

using namespace std;

const int MAX_SIZE = 30;

class Vector {
private:
    int size;
    int* data;

public:
    Vector();
    Vector(int s);
    Vector(const Vector& other);
    ~Vector();

    Vector& operator=(const Vector& other);

    int& operator[](int index);
    const int& operator[](int index) const;

    int operator()() const;

    Vector& operator--();
    Vector operator--(int);

    friend ostream& operator<<(ostream& out, const Vector& v);
    friend istream& operator>>(istream& in, Vector& v);
};