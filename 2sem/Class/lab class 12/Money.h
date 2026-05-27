#pragma once
#include <iostream>

using namespace std;

class Money
{
private:
    long rub;
    int kop;
    void normalize();
    long to_kop() const;

public:
    Money();
    Money(long r, int k);
    Money(const Money& m);
    ~Money();

    Money& operator=(const Money& m);
    Money operator+(const Money& m) const;
    Money operator/(int n) const;

    bool operator<(const Money& m) const;
    bool operator>(const Money& m) const;
    bool operator==(const Money& m) const;

    friend istream& operator>>(istream& in, Money& m);
    friend ostream& operator<<(ostream& out, const Money& m);
};
