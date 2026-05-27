#include <iostream>
#include "Person.h"

Person::Person() : name("NoName"), age(20) {}

Person::Person(std::string name, int age) : name(name), age(age) {
    SetAge(age);
}

Person::Person(const Person &obj) : name(obj.name), age(obj.age) {}
Person::~Person() {}

void Person::HandleEvent(const TEvent &e) {
    if(e.what == evMessage) {
        switch(e.command) {
            case cmGet:
                std::cout<<"Age = "<< GetAge() << std::endl;
                break;
        }
    }
}

Person& Person::operator=(const Person &obj) {
    if (&obj == this) {
        return *this;
    }
    name = obj.name;
    age = obj.age;

    return *this;
}

void Person::SetName(std::string name) {
    this->name = name;
}

void Person::SetAge(int) {
    if (age > 0 && age < 120) {
        this->age = age;
        return;
    }
    throw std::invalid_argument("Age isn`t correct!");
}

std::string Person::GetName() const {
    return name;
}

int Person::GetAge() const {
    return age;
}
        
void Person::Show() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
}

void Person::Input() {
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter age: ";
    std::cin >> age;
    SetAge(age);
}