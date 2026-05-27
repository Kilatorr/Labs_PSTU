#pragma once

#include <iostream>

using namespace std;

class Set;

class Iterator {
    friend class Set;
public:
    Iterator(void);
    Iterator(const Iterator& it);

    bool operator==(const Iterator& it);
    bool operator!=(const Iterator& it);
    void operator++();
    void operator++(int);
    int& operator*() const;

private:
    int* elem;
};

class Set {
public:
    Set(int s = 0);
    Set(const Set& a);
    ~Set(void);

    Set& operator=(const Set& a);
    int& operator[](int index);
    int operator()();
    Set operator+(const Set& a);

    void Add(int value);
    bool Contains(int value);

    Iterator first();
    Iterator last();

    friend ostream& operator<<(ostream& out, const Set& a);
    friend istream& operator>>(istream& in, Set& a);

private:
    int size;
    int* data;
    Iterator beg;
    Iterator end;

    void update_iterators();
};
