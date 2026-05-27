#pragma once
#include "Object.h"
#include <iostream>
using namespace std;

class Vector {
private:
    Object** beg;
    int size;
    int cur;

public:
    Vector();
    Vector(int);
    ~Vector();

    void Add(Object*);

    friend ostream& operator<<(ostream&, const Vector&);
};
