#include <iostream>
#ifndef SET
#define SET

template <class T>
class Set {
    private:
        int size;
        T * data;
    public:
        Set();
        Set(int);
        Set (const Set<T>&);
        ~Set();

        Set<T>& operator=(const Set<T>&);
        Set<T> operator+(const Set<T>&);

        T& operator[](int);
        int operator()();
        
        friend std::istream& operator>>(std::istream &in, Set<T> &obj) {
            if (obj.data == nullptr || obj.size == 0) {
                std::cout << "Size of set is 0" << std::endl;
                return in;
            }

            int count = 0;
            while (count < obj.size) {
                T elem;
                std::cout << "Enter element " << (count + 1) << ": " << std::endl;
                in >> elem;

                bool isIn = false;
                for (int i = 0; i < count; ++i) {
                    if (obj.data[i] == elem) {
                        isIn = true;
                        break;
                    }
                }

                if (!isIn) {
                    obj.data[count++] = elem;
                } else {
                    std::cout << "Duplicate! Enter again" << std::endl;
                }
            }
            return in;
        }

        friend std::ostream& operator<<(std::ostream &out, const Set<T> &obj) {
            if (obj.data == nullptr) {
                out << "{}" << std::endl;
        
                return out;
            }
    
            std::cout << "{" << std::endl; 
            for (int i = 0; i < obj.size; i++) {
                out << obj.data[i]; 
            }
            out << "}" << std::endl;

            return out;
        }
};
#endif

template <class T>
Set<T>::Set() : size(0), data(nullptr) {}

template <class T>
Set<T>::Set(int size) : size(size) {
    if (size > 0) {
        data = new T[size];
    }
}

template <class T>
Set<T>::Set(const Set &obj) {
    size = obj.size;

    if (size > 0) {
        data = new T[size];

        for (int i = 0; i < size; i++) {
            data[i] = obj.data[i];
        }
    }
}

template <class T>
Set<T>::~Set() {
    if (data != nullptr) {
        delete[] data;
    }
}

template <class T>
Set<T>& Set<T>::operator=(const Set &obj) {
    if (&obj == this) {
        return *this;
    }
    delete[] data;

    data = nullptr;
    size = obj.size;

    if (size > 0) {
        data = new T[size]; 

        for (int i = 0; i < size; i++) {
            data[i] = obj.data[i];
        }
    }

    return *this;
}

template <class T>
T& Set<T>::operator[](int idx) {
    if (idx >= 0 && idx < size) {
        return data[idx];
    }
    throw std::out_of_range("Index out of range");
}

template <class T>
int Set<T>::operator()() {
    return size;
}

template <class T>
Set<T> Set<T>::operator+(const Set<T> &obj) {
    int new_size = size;
    T * temp = new T[size + obj.size];

    for (int i = 0; i < size; i++) {
        temp[i] = data[i];
    }

    for (int i = 0; i < obj.size; i++) {
        bool isIn = false;
        for (int j = 0; j < new_size; j++) {
            if (temp[j] == obj.data[i]) {
                isIn = true;
                break;
            }
        }
        if (!isIn) {
            temp[new_size++] = obj.data[i];
        }
    }

    Set<T> res(new_size);
    for (int i = 0; i < new_size; i++) {
        res.data[i] = temp[i];
    }
    delete[] temp;
    return res;  
}