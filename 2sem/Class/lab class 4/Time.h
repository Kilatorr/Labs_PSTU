#include <iostream>
using namespace std;
#pragma once
#include "Triad.h"

class Time : public Triad {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time();
    Time(int, int, int);
    Time(const Time&);
    ~Time();

    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;
    void setHours(int);
    void setMinutes(int);
    void setSeconds(int);

    Time& operator=(const Time&);
    bool operator==(const Time&) const;
    bool operator!=(const Time&) const;
    bool operator<(const Time&) const;
    bool operator>(const Time&) const;
    bool operator<=(const Time&) const;
    bool operator>=(const Time&) const;

    friend ostream& operator<<(ostream&, const Time&);
    friend istream& operator>>(istream&, Time&);
};