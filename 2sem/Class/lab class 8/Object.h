#ifndef OBJECT
#define OBJECT
#include "Event.h"

class Object {
    protected:
        Object();
    public:
        virtual void Show() = 0;
        virtual void Input() = 0;
        virtual void HandleEvent(const TEvent&) = 0;
        virtual ~Object();
};
#endif