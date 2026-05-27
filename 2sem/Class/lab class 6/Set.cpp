#include "Set.h"

Iterator::Iterator(void) {
    elem = 0;
}

Iterator::Iterator(const Iterator& it) {
    elem = it.elem;
}

bool Iterator::operator==(const Iterator& it) {
    return elem == it.elem;
}

bool Iterator::operator!=(const Iterator& it) {
    return elem != it.elem;
}

void Iterator::operator++() {
    ++elem;
}

void Iterator::operator++(int) {
    elem++;
}

int& Iterator::operator*() const {
    return *elem;
}

Set::Set(int s) {
    size = s;

    if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    } else {
        data = 0;
    }

    update_iterators();
}

Set::Set(const Set& a) {
    size = a.size;

    if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = a.data[i];
        }
    } else {
        data = 0;
    }

    update_iterators();
}

Set::~Set(void) {
    if (data != 0) {
        delete[] data;
    }
    data = 0;
}

void Set::update_iterators() {
    if (data == 0) {
        beg.elem = 0;
        end.elem = 0;
    } else {
        beg.elem = &data[0];
        end.elem = &data[size];
    }
}

Set& Set::operator=(const Set& a) {
    if (this == &a) {
        return *this;
    }

    if (data != 0) {
        delete[] data;
    }

    size = a.size;

    if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = a.data[i];
        }
    } else {
        data = 0;
    }

    update_iterators();
    return *this;
}

int& Set::operator[](int index) {
    static int error = 0;

    if (index >= 0 && index < size) {
        return data[index];
    }

    cout << "Error! Index >= size" << endl;
    return error;
}

int Set::operator()() {
    return size;
}

bool Set::Contains(int value) {
    for (int i = 0; i < size; i++) {
        if (data[i] == value) {
            return true;
        }
    }
    return false;
}

void Set::Add(int value) {
    if (Contains(value)) {
        return;
    }

    int* temp = new int[size + 1];

    for (int i = 0; i < size; i++) {
        temp[i] = data[i];
    }

    temp[size] = value;

    if (data != 0) {
        delete[] data;
    }

    data = temp;
    size++;
    update_iterators();
}

Set Set::operator+(const Set& a) {
    Set temp;

    for (int i = 0; i < size; i++) {
        temp.Add(data[i]);
    }

    for (int i = 0; i < a.size; i++) {
        temp.Add(a.data[i]);
    }

    return temp;
}

Iterator Set::first() {
    return beg;
}

Iterator Set::last() {
    return end;
}

ostream& operator<<(ostream& out, const Set& a) {
    if (a.size == 0) {
        out << "Empty";
    }

    for (int i = 0; i < a.size; i++) {
        out << a.data[i] << " ";
    }

    return out;
}

istream& operator>>(istream& in, Set& a) {
    int n = a.size;
    int value;

    if (a.data != 0) {
        delete[] a.data;
    }

    a.data = 0;
    a.size = 0;
    a.update_iterators();

    for (int i = 0; i < n; i++) {
        cout << "element[" << i << "] = ";
        in >> value;

        if (a.Contains(value)) {
            cout << "Takoi element uzhe est" << endl;
            i--;
        } else {
            a.Add(value);
        }
    }

    return in;
}
