#include "Triad.h"

Triad::Triad() {
    first = 0;
    second = 0;
    third = 0;
}

Triad::Triad(int f, int s, int t) {
    first = f;
    second = s;
    third = t;
}

Triad::Triad(const Triad& t) {
    first = t.first;
    second = t.second;
    third = t.third;
}

Triad::~Triad() {}

int Triad::getFirst() const { return first; }
int Triad::getSecond() const { return second; }
int Triad::getThird() const { return third; }
void Triad::setFirst(int f) { first = f; }
void Triad::setSecond(int s) { second = s; }
void Triad::setThird(int t) { third = t; }

Triad& Triad::operator=(const Triad& t) {
    if (this != &t) {
        first = t.first;
        second = t.second;
        third = t.third;
    }
    return *this;
}

bool Triad::operator==(const Triad& t) const {
    return first == t.first && second == t.second && third == t.third;
}

bool Triad::operator<(const Triad& t) const {
    if (first < t.first) return true;
    if (first > t.first) return false;
    if (second < t.second) return true;
    if (second > t.second) return false;
    return third < t.third;
}

bool Triad::operator>(const Triad& t) const {
    return !(*this == t) && !(*this < t);
}

void Triad::Show() {
    cout << "Triad: (" << first << ":" << second << ":" << third << ")" << endl;
}

ostream& operator<<(ostream& out, const Triad& t) {
    out << "(" << t.first << ":" << t.second << ":" << t.third << ")";
    return out;
}

istream& operator>>(istream& in, Triad& t) {
    cout << "Первое: "; in >> t.first;
    cout << "Второе: "; in >> t.second;
    cout << "Третье: "; in >> t.third;
    return in;
}
