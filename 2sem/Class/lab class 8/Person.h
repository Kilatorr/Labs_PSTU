#include <string>
#include "Object.h"
#ifndef PERSON
#define PERSON

class Person: public Object {
    protected:
        std::string name;
        int age;
    public:
        Person();
        Person(std::string, int);
        Person(const Person&);
        virtual ~Person();

        void HandleEvent(const TEvent&);

        Person& operator=(const Person&);

        void SetName(std::string);
        void SetAge(int);

        std::string GetName() const;
        int GetAge() const; 
        
        void Show() override;
        void Input() override;
};

#endif