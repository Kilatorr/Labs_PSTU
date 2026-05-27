#pragma once
#include "Object.h"
#include <iostream>
using namespace std;

class Triad : public Object {
protected:
    int first;
    int second;
    int third;

public:
    Triad();
    Triad(int, int, int);
    Triad(const Triad&);
    virtual ~Triad();

    int getFirst() const;
    int getSecond() const;
    int getThird() const;
    void setFirst(int);
    void setSecond(int);
    void setThird(int);

    Triad& operator=(const Triad&);
    bool operator==(const Triad&) const;
    bool operator<(const Triad&) const;
    bool operator>(const Triad&) const;

    virtual void Show();

    friend ostream& operator<<(ostream&, const Triad&);
    friend istream& operator>>(istream&, Triad&);
};
