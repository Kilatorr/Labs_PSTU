#pragma once
#include <string>

using namespace std;

class Error {
private:
    string message;

public:
    Error(int code) {
        switch (code) {
        case 1:
            message = "Ошибка: размер вектора больше MAX_SIZE";
            break;
        case 2:
            message = "Ошибка: индекс меньше 0";
            break;
        case 3:
            message = "Ошибка: индекс больше или равен размеру вектора";
            break;
        case 5:
            message = "Ошибка: попытка удалить элемент из пустого вектора";
            break;
        default:
            message = "Неизвестная ошибка";
            break;
        }
    }

    string what() const {
        return message;
    }
};