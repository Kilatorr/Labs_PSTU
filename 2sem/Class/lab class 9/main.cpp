#include <iostream>
#include "Vector.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        int n;

        cout << "Введите размер вектора: ";
        cin >> n;

        Vector v(n);
        cin >> v;

        cout << "Исходный ";
        cout << v;

        cout << "Размер вектора: " << v() << endl;

        int index;
        cout << "Введите индекс элемента: ";
        cin >> index;

        cout << "Элемент с индексом " << index << ": " << v[index] << endl;
        cout << endl;

        cout << "Удаляем первый элемент" << endl;
        --v;
        cout << v;

        cout << endl;
        cout << "Удаляем последний элемент" << endl;
        v--;
        cout << v;
    }
    catch (const Error& e) {
        cout << e.what() << endl;
    }

    cout << endl;
    cout << "Проверка исключительных ситуаций:" << endl;

    try {
        Vector a(31);
    }
    catch (const Error& e) {
        cout << e.what() << endl;
    }

    try {
        Vector b(3);
        cout << b[-1] << endl;
    }
    catch (const Error& e) {
        cout << e.what() << endl;
    }

    try {
        Vector c(3);
        cout << c[10] << endl;
    }
    catch (const Error& e) {
        cout << e.what() << endl;
    }

    try {
        Vector d;
        --d;
    }
    catch (const Error& e) {
        cout << e.what() << endl;
    }

    try {
        Vector e;
        e--;
    }
    catch (const Error& e) {
        cout << e.what() << endl;
    }

    return 0;
}