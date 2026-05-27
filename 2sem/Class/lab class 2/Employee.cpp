#include "Employee.h"
#include <iostream>
using namespace std;

Employee::Employee() {
    name = "";
    position = "";
    salary = 0;
    cout << "Конструктор без параметров для объекта " << this << endl;
}

Employee::Employee(string n, string p, double s) {
    name = n;
    position = p;
    salary = s;
    cout << "Конструктор с параметрами для объекта " << this << endl;
}

Employee::Employee(const Employee& e) {
    name = e.name;
    position = e.position;
    salary = e.salary;
    cout << "Конструктор копирования для объекта " << this << endl;
}

Employee::~Employee() {
    cout << "Деструктор для объекта " << this << endl;
}

string Employee::getName() { return name; }
string Employee::getPosition() { return position; }
double Employee::getSalary() { return salary; }

void Employee::setName(string n) { name = n; }
void Employee::setPosition(string p) { position = p; }
void Employee::setSalary(double s) { salary = s; }

void Employee::show() {
    cout << "Сотрудник: " << name << ", должность: " << position << ", зарплата: " << salary << endl;
}