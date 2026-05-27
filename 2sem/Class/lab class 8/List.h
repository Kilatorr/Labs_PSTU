#ifndef LIST
#define LIST
#include "Object.h"
#include "Event.h"

class List {
    protected:
        int size;
        Object ** beg;
    public:
        List();
        List(unsigned int);
        List(const List&);
        ~List();

        void HandleEvent(const TEvent&);

        List& operator=(const List&);
        Object*& operator[](int);
        int operator()();

        void Show() const;
        void Add();
        void Del();
};

#endif