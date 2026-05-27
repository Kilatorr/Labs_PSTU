#include <iostream>
#ifndef MONEY
#define MONEY

class Money {
    long Rubles;
    int Pennies;

    public:
        Money();
        Money(long, int);
        Money(const Money&);
        ~Money();

        Money& operator=(const Money&);

        Money operator+(const Money&);
        Money operator-(const Money&);

        bool operator==(const Money&) const;
       
        friend std::istream& operator>>(std::istream&, Money&);
        friend std::ostream& operator<<(std::ostream&, Money&);

        void SetRubles(long);
        void SetPennies(int);

        long GetRubles() const;
        int GetPennies() const;
};
#endif