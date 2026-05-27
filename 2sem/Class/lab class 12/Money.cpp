#include "Money.h"

Money::Money()
{
    rub = 0;
    kop = 0;
}

Money::Money(long r, int k)
{
    rub = r;
    kop = k;
    normalize();
}

Money::Money(const Money& m)
{
    rub = m.rub;
    kop = m.kop;
}

Money::~Money()
{
}

void Money::normalize()
{
    long total = rub * 100 + kop;
    rub = total / 100;
    kop = total % 100;
}

long Money::to_kop() const
{
    return rub * 100 + kop;
}

Money& Money::operator=(const Money& m)
{
    if (this == &m) return *this;
    rub = m.rub;
    kop = m.kop;
    return *this;
}

Money Money::operator+(const Money& m) const
{
    long total = to_kop() + m.to_kop();
    return Money(total / 100, (int)(total % 100));
}

Money Money::operator/(int n) const
{
    if (n == 0) return Money();
    long total = to_kop() / n;
    return Money(total / 100, (int)(total % 100));
}

bool Money::operator<(const Money& m) const
{
    return to_kop() < m.to_kop();
}

bool Money::operator>(const Money& m) const
{
    return to_kop() > m.to_kop();
}

bool Money::operator==(const Money& m) const
{
    return to_kop() == m.to_kop();
}

istream& operator>>(istream& in, Money& m)
{
    cout << "rub: ";
    in >> m.rub;
    cout << "kop: ";
    in >> m.kop;
    m.normalize();
    return in;
}

ostream& operator<<(ostream& out, const Money& m)
{
    out << m.rub << ",";
    if (m.kop < 10) out << "0";
    out << m.kop;
    return out;
}
