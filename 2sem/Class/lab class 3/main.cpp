#include "Money.h"
#include <iostream>
using namespace std;
#include <clocale>
int main() {
    setlocale(LC_ALL, "Russian");
    
    Money m1, m2, m3;
    
    cout << "Введите первую сумму:\n";
    cin >> m1;
    cout << "Введите вторую сумму:\n";
    cin >> m2;
    
    cout << "\nПервая сумма: " << m1 << endl;
    cout << "Вторая сумма: " << m2 << endl;
    

    if (m1 == m2){
        cout << "Суммы равны" << endl;
    } else {
        cout << "Суммы не равны" << endl;
    }
    cout << "\nПрефиксный -- (уменьшение на копейку):" << endl;
    cout << "Было: " << m1 << endl;
    cout << "Результат: " << --m1 << endl;
    
    cout << "\nПостфиксный -- (уменьшение на копейку):" << endl;
    m3 = m2--;
    cout << "m2-- = " << m3 << endl;
    cout << "m2 после операции: " << m2 << endl;
    
    m3 = m1;
    cout << "\nПосле присваивания m3 = m1: " << m3 << endl;
    
    return 0;
}