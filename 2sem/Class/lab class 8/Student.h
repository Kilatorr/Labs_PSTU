#ifndef STUDENT
#define STUDENT
#include "Person.h"
#include <string>

class Student: public Person {
    private:
        float rating;
    public:
        Student();
        Student(std::string, int, float);
        Student(const Student&);
        ~Student();

        Student& operator=(const Student&);

        void SetRating(float);
        float GetRating() const;

        void Show() override;
        void Input() override;
};

#endif