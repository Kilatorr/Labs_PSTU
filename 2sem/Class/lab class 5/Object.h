#pragma once
class Object {
public:
    Object() {}
    virtual ~Object() {}
    virtual void Show() = 0;
};
