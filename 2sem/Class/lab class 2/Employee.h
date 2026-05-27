#pragma once
#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string name;
    string position;
    double salary;
    
public:
    Employee();
    Employee(string, string, double);
    Employee(const Employee&);
    ~Employee();
    
    string getName();
    string getPosition();
    double getSalary();
    
    void setName(string);
    void setPosition(string);
    void setSalary(double);
    
    void show();
};