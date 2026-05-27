#include "Vector.h"

Vector::Vector(): size(0), data(nullptr) {}
Vector::Vector(int s) {
    if (s < 0 || s > MAX_SIZE) {
        throw Error(1);
    }

    size = s;

    if (size == 0) {
        data = nullptr;
    }
    else {
        data = new int[size];

        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
}

Vector::Vector(const Vector& other) {
    size = other.size;

    if (size == 0) {
        data = nullptr;
    }
    else {
        data = new int[size];

        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
}

Vector::~Vector() {delete[] data;}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data;

        size = other.size;

        if (size == 0) {
            data = nullptr;
        }
        else {
            data = new int[size];

            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
    }

    return *this;
}

int& Vector::operator[](int index) {
    if (index < 0) {
        throw Error(2);
    }

    if (index >= size) {
        throw Error(3);
    }

    return data[index];
}

const int& Vector::operator[](int index) const {
    if (index < 0) {
        throw Error(2);
    }

    if (index >= size) {
        throw Error(3);
    }

    return data[index];
}

int Vector::operator()() const {return size;}

Vector& Vector::operator--() {
    if (size == 0) {
        throw Error(5);
    }

    for (int i = 0; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    size--;

    return *this;
}

Vector Vector::operator--(int) {
    if (size == 0) {
        throw Error(5);
    }
    Vector temp(*this);
    size--;

    return temp;
}

ostream& operator<<(ostream& out, const Vector& v) {
    if (v.size == 0) {
        out << "Вектор пуст" << endl;
        return out;
    }

    out << "Вектор: ";

    for (int i = 0; i < v.size; i++) {
        out << v.data[i] << " ";
    }

    out << endl;

    return out;
}

istream& operator>>(istream& in, Vector& v) {
    for (int i = 0; i < v.size; i++) {
        cout << "Введите элемент [" << i << "]: ";
        in >> v.data[i];
    }

    return in;
}