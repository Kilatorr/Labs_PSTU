#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include "time.h"

using namespace std;

const string FILE_NAME = "time.txt";
const string TEMP_FILE = "temp.txt";

void CopyFile(const string& from, const string& to) {
    ifstream fin(from);
    ofstream fout(to);

    Time t;

    while (fin >> t) {
        fout << t << endl;
    }

    fin.close();
    fout.close();
}

void CreateFile() {
    ofstream fout(FILE_NAME);

    if (!fout) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    int n;
    cout << "Введите количество записей: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Time t;

        cout << "Введите время в формате минуты:секунды: ";
        cin >> t;

        fout << t << endl;
    }

    fout.close();

    cout << "Файл создан" << endl;
}

void PrintFile() {
    ifstream fin(FILE_NAME);

    if (!fin) {
        cout << "Файл не найден" << endl;
        return;
    }

    Time t;
    int number = 1;
    bool empty = true;

    cout << "Содержимое файла:" << endl;

    while (fin >> t) {
        cout << number << ") " << t << endl;
        number++;
        empty = false;
    }

    if (empty) {
        cout << "Файл пуст" << endl;
    }

    fin.close();
}

void DeleteFromRange() {
    ifstream fin(FILE_NAME);

    if (!fin) {
        cout << "Файл не найден" << endl;
        return;
    }

    ofstream fout(TEMP_FILE);

    Time k1;
    Time k2;

    cout << "Введите k1 в формате минуты:секунды: ";
    cin >> k1;

    cout << "Введите k2 в формате минуты:секунды: ";
    cin >> k2;

    if (k1.ToSeconds() > k2.ToSeconds()) {
        Time temp = k1;
        k1 = k2;
        k2 = temp;
    }

    Time t;

    while (fin >> t) {
        if (!t.InRange(k1, k2)) {
            fout << t << endl;
        }
    }

    fin.close();
    fout.close();

    CopyFile(TEMP_FILE, FILE_NAME);

    cout << "Записи из интервала удалены" << endl;
}

void IncreaseByValue() {
    ifstream fin(FILE_NAME);

    if (!fin) {
        cout << "Файл не найден" << endl;
        return;
    }

    ofstream fout(TEMP_FILE);

    Time value;

    cout << "Введите значение, которое нужно увеличить, в формате минуты:секунды: ";
    cin >> value;

    Time t;

    while (fin >> t) {
        if (t == value) {
            t.AddSeconds(90);
        }

        fout << t << endl;
    }

    fin.close();
    fout.close();

    CopyFile(TEMP_FILE, FILE_NAME);

    cout << "Подходящие записи увеличены на 1 минуту 30 секунд" << endl;
}

void AddToBegin() {
    ofstream fout(TEMP_FILE);

    if (!fout) {
        cout << "Ошибка открытия временного файла" << endl;
        return;
    }

    int k;

    cout << "Введите количество добавляемых записей: ";
    cin >> k;

    for (int i = 0; i < k; i++) {
        Time t;

        cout << "Введите новую запись в формате минуты:секунды: ";
        cin >> t;

        fout << t << endl;
    }

    ifstream fin(FILE_NAME);

    Time oldTime;

    while (fin >> oldTime) {
        fout << oldTime << endl;
    }

    fin.close();
    fout.close();

    CopyFile(TEMP_FILE, FILE_NAME);

    cout << "Новые записи добавлены в начало файла" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Создание файла" << endl;
    CreateFile();

    cout << "Исходное содержимое файла:" << endl;
    PrintFile();
    cout << endl;

    cout << "Удаление записей из интервала от k1 до k2" << endl;
    DeleteFromRange();

    cout << "Файл после удаления:" << endl;
    PrintFile();
    cout << endl;

    cout << "Увеличение записей с заданным значением на 1 минуту 30 секунд" << endl;
    IncreaseByValue();

    cout << "Файл после увеличения:" << endl;
    PrintFile();
    cout << endl;

    cout << "Добавление K записей в начало файла" << endl;
    AddToBegin();

    cout << "Итоговое содержимое файла:" << endl;
    PrintFile();

    return 0;
}