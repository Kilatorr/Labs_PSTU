#include <iostream>
#include "Money.h"

using namespace std;

Money::Money() : Rubles(0), Pennies(0) {}

Money::Money(long rubles, int pennies) : Rubles(rubles), Pennies(pennies) {
    SetRubles(Rubles);
    SetPennies(Pennies);
}

Money::Money(const Money &other) {
    Rubles = other.Rubles;
    Pennies = other.Pennies;
}
Money::~Money() {};

bool Money::operator==(const Money &other) const {
    if (Rubles == other.Rubles && Pennies == other.Pennies) {
        return true;
    }
    return false;
}

void Money::SetRubles(long summ) {
    if (summ >= 0) {
        Rubles = summ;
    }
    else {
        cout << "Error! Rubles < 0" << endl;
    }
}

void Money::SetPennies(int summ) {
    if (summ >= 0) {
        Rubles += summ / 100;
        Pennies = summ % 100;
    }
    else {
        cout << "Error! Pennies < 0" << endl;
    }
}

long Money::GetRubles() const {
    return Rubles;
}

int Money::GetPennies() const {
    return Pennies;
}

Money& Money::operator=(const Money &m) {
    if (&m == this) {
        return *this;
    }
    Rubles = m.Rubles;
    Pennies = m.Pennies;
    return *this;
}

Money Money::operator+(const Money& other) {
    long rub = Rubles + other.Rubles + (Pennies + other.Pennies) / 100;
    int pen = (Pennies + other.Pennies) % 100;
    return Money(rub, pen);
}

Money Money::operator-(const Money& other) {
    if ((Rubles < other.Rubles) || (Rubles == other.Rubles && Pennies < other.Pennies)) {
        cout << "Error! Balance < 0" << endl;
        return Money(0, 0);
    }
    long rub = (Rubles - other.Rubles);
    int pen = (Pennies - other.Pennies);

    if (pen < 0) {
        rub--;
        pen = (100 - abs(pen));
    }
    
    return Money(rub, pen);
}

istream& operator>>(istream &in, Money &obj) {
    long rub;
    int pen;
    cout << "Rubles: ";
    in >> rub;
    cout << "Pennie: ";
    in >> pen;

    obj.SetRubles(rub);
    obj.SetPennies(pen);

    return in;
}

ostream& operator<<(ostream &out, Money &obj) {
    cout << "Balance: " << obj.GetRubles();

    if (obj.GetPennies() < 10) {
        cout << ",0" << obj.GetPennies() << " rub" << endl;
    }
    else {
        cout << "," << obj.GetPennies() << " rub" << endl;
    }

    return out;
}