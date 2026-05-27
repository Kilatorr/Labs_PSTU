#include <iostream>
#include "List.h"
#include "Object.h"
#include "Person.h"
#include "Student.h"

List::List() : size(0), beg(nullptr) {}

List::List(unsigned int size) : size(size), beg(nullptr) {
    if (size > 0) {
        beg = new Object*[size];

        for (int i = 0; i < size; i++) {
            beg[i] = nullptr;
        }
    }
}

List::List(const List &obj) {
    size = obj.size;

    if (size > 0) {
        beg = new Object*[size];

        for (int i = 0; i < size; i++) {
            beg[i] = obj.beg[i];
        }
    }
    else {
        beg = nullptr;
    }
}

List::~List() {
    delete[] beg;
    beg = nullptr;
}

void List::HandleEvent(const TEvent &e) {
    if (beg == nullptr) {
        return;
    }
    if(e.what == evMessage) {
        Object ** p = beg;
        for(int i = 0; i < size; i++) {
            if (*p == nullptr) {
                std::cout << "-" << std::endl;
            }
            else {
                (*p)->HandleEvent(e);
                p++;
            }
        }
    }
}

List& List::operator=(const List &obj) {
    if (&obj == this) {
        return *this;
    }
    delete[] beg;
    size = obj.size;

    if (size > 0) {
        beg = new Object*[size];

        for (int i = 0; i < size; i++) {
            beg[i] = obj.beg[i];
        }
    }
    else {
        beg = nullptr;
    }
    return *this;
}

Object*& List::operator[](int idx) {
    if (idx >= 0 && idx < size) {
        return beg[idx];
    }
    throw std::out_of_range("Index out of range");
}

int List::operator()() {
    return size;
}

void List::Show() const {
    if (size <= 0 || beg == nullptr) {
        std::cout << "[]" << std::endl;
    }
    else {
        std::cout << "[" << std::endl;

        for (int i = 0; i < size; i++) {
            if (beg[i] == nullptr) {
                std::cout << "-" << std::endl;
            }
            else {
                beg[i]->Show();
            std::cout << std::endl;
            }
        }
        std::cout << "]" << std::endl;
    }
}

void List::Add() {
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            if (beg[i] == nullptr) {
                std::cout << "1. Person" << std::endl;
                std::cout << "2. Student" << std::endl;
                std::cout << "> ";

                Object * p;
                int com;
                std::cin >> com;

                if (com == 1) {
                    Person * a = new Person;
                    a->Input();
                    p = a;
                }
                else if (com == 2) {
                    Student * b = new Student;
                    b->Input();
                    p = b;
                }
                else {
                    return;
                }
                beg[i] = p;
                return;
            }
        }
        std::cout << "List is full" << std::endl;
        return;
    }
    else {
        std::cout << "List`s size is 0" << std::endl;
        return;
    }
}

void List::Del() {
    if (size >= 1) {
        int idx;
        std::cout << "Enter idx of elem: ";
        std::cin >> idx;

        if (idx >= 0 && idx < size) {
            if (beg[idx] != nullptr) {
                delete beg[idx];
                beg[idx] = nullptr;
            }
            return;
        }
        throw std::out_of_range("Index if out of range");
    }
    std::cout << "List is empty" << std::endl;
    return;
}