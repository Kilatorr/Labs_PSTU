#include <iostream>
#include "Student.h"
#include "Person.h"

Student::Student() : Person(), rating(5.0) {}

Student::Student(std::string name, int age, float rating) : Person(name, age), rating(rating) {
    SetRating(rating);
}

Student::Student(const Student &obj) : Person(obj.name, obj.age), rating(obj.rating) {}
Student::~Student() {}

Student& Student::operator=(const Student &obj) {
    if (&obj == this) {
        return *this;
    }
    name = obj.name;
    age = obj.age;
    rating - obj.rating;

    return *this;
}

void Student::SetRating(float rating) {
    if (rating >= 0.0 && rating <= 10.0) {
        this->rating = rating;
        return;
    }
    throw std::invalid_argument("Rating isn`t correct");
}

float Student::GetRating() const {
    return rating;
}

void Student::Show() {
    Person::Show();
    std::cout << "Rating: " << rating << std::endl;
}

void Student::Input() {
    Person::Input();
    std::cout << "Rating: ";
    std::cin >> rating;
    SetRating(rating);
}