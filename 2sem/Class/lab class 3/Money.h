#pragma once
#include <iostream>
using namespace std;

class Money {
private:
    long rubles;
    int kopecks;
    
public:
    Money();
    Money(long, int);
    Money(const Money&);
    ~Money();
    
    long getRubles() const;
    int getKopecks() const;
    void setRubles(long);
    void setKopecks(int);
    
    Money& operator=(const Money&);
    bool operator==(const Money&) const;
    bool operator!=(const Money&) const;
    
    Money& operator--();
    Money operator--(int);
    
    friend ostream& operator<<(ostream&, const Money&);
    friend istream& operator>>(istream&, Money&);
};