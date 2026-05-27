#pragma once
#include <iostream>

using namespace std;

class Time {
private:
    int mins;
    int secs;

    void Normalize();

public:
    Time();
    Time(int m, int s);

    int ToSeconds() const; // перевод всего времени в секунды

    void AddSeconds(int s); // добавление секунд

    bool InRange(const Time& left, const Time& right) const;

    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;

    friend ostream& operator<<(ostream& out, const Time& t);
    friend istream& operator>>(istream& in, Time& t);
};