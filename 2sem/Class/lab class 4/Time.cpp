#include <iostream>
using namespace std;
#include "Time.h"

Time::Time() : Triad() {
    hours = 0; minutes = 0; seconds = 0;
}

Time::Time(int h, int m, int s) : Triad(h, m, s) {
    hours = h; minutes = m; seconds = s;
}

Time::Time(const Time& t) : Triad(t) {
    hours = t.hours; minutes = t.minutes; seconds = t.seconds;
}

Time::~Time() {}

int Time::getHours() const { return hours; }
int Time::getMinutes() const { return minutes; }
int Time::getSeconds() const { return seconds; }
void Time::setHours(int h) { hours = h; }
void Time::setMinutes(int m) { minutes = m; }
void Time::setSeconds(int s) { seconds = s; }

Time& Time::operator=(const Time& t) {
    if (this != &t) {
        Triad::operator=(t);
        hours = t.hours; minutes = t.minutes; seconds = t.seconds;
    }
    return *this;
}

bool Time::operator==(const Time& t) const {
    return hours == t.hours && minutes == t.minutes && seconds == t.seconds;
}

bool Time::operator!=(const Time& t) const { return !(*this == t); }

bool Time::operator<(const Time& t) const {
    if (hours < t.hours) return true;
    if (hours > t.hours) return false;
    if (minutes < t.minutes) return true;
    if (minutes > t.minutes) return false;
    return seconds < t.seconds;
}

bool Time::operator>(const Time& t) const { return !(*this == t) && !(*this < t); }
bool Time::operator<=(const Time& t) const { return !(*this > t); }
bool Time::operator>=(const Time& t) const { return !(*this < t); }

ostream& operator<<(ostream& out, const Time& t) {
    out << t.hours << ":" << t.minutes << ":" << t.seconds;
    return out;
}

istream& operator>>(istream& in, Time& t) {
    cout << "Часы: "; in >> t.hours;
    cout << "Минуты: "; in >> t.minutes;
    cout << "Секунды: "; in >> t.seconds;
    return in;
}