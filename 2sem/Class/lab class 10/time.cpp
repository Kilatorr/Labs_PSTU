#include "Time.h"

Time::Time(): mins(0), secs(0) {}

Time::Time(int m, int s): mins(m), secs(s) {}

void Time::Normalize() {
    if (secs >= 60) {
        mins += secs / 60;
        secs = secs % 60;
    }

    while (secs < 0) {
        mins--;
        secs += 60;
    }

    if (mins < 0) {
        mins = 0;
        secs = 0;
    }
}

int Time::ToSeconds() const {
    return mins * 60 + secs;
}

void Time::AddSeconds(int s) {
    secs += s;
    Normalize();
}

bool Time::InRange(const Time& left, const Time& right) const {
    int current = ToSeconds();

    return current >= left.ToSeconds() && current <= right.ToSeconds();
}

bool Time::operator==(const Time& other) const {
    return mins == other.mins && secs == other.secs;
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& out, const Time& t) {
    out << t.mins << ":";

    if (t.secs < 10) {
        out << "0";
    }

    out << t.secs;

    return out;
}

istream& operator>>(istream& in, Time& t) {
    int m;
    int s;
    char colon;

    in >> m >> colon >> s;

    if (in && colon == ':') {
        t.mins = m;
        t.secs = s;
        t.Normalize();
    }
    else {
        in.setstate(ios::failbit);
    }

    return in;
}