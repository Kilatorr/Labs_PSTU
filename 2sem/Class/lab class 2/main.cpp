#include "Employee.h"
#include <iostream>
#include <clocale>
using namespace std;

Employee make_employee() {
    string n, p;
    double s;
    cout << "Введите ФИО: ";
    cin >> n;
    cout << "Введите должность: ";
    cin >> p;
    cout << "Введите зарплату: ";
    cin >> s;
    Employee emp(n, p, s);
    return emp;
}

void print_employee(Employee e) {
    e.show();
}

int main() {
    setlocale(LC_ALL, "Russian");

    Employee e1;
    e1.show();
    
    Employee e2("Мичков И.И.", "менеджер", 50000);
    e2.show();
    
    Employee e3 = e2;
    e3.setName("Сюзев М.М.");
    e3.setPosition("директор");
    e3.setSalary(80000);
    
    print_employee(e3);
    
    e1 = make_employee();
    e1.show();
    
    return 0;
}