#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

using namespace std;

struct music {
    char naz[100];
    char aut[100];
    int time;
    int price;
    void nap() {
        cout << " Название: " << naz << endl;
        cout << " Автор: " << aut << endl;
        cout << " Продолжительность: " << time << " секунд" << endl;
        cout << " Цена: " << price << " ₽" << endl;
    }
};

music input() {
    music m;
    string br;
    cout << "название: "; getline(cin, br);
    int l1 = br.copy(m.naz, 99);
    m.naz[l1] = '\0';

    cout << "автор: "; getline(cin, br);
    int l2 = br.copy(m.aut, 99);
    m.aut[l2] = '\0';

    cout << "продолжительность: ";
    getline(cin, br);
    m.time = stoi(br);

    cout << "цена: ";
    getline(cin, br);
    m.price = stoi(br);
    return m;
}

music* del_el(music* m, int& n, int tt) {
    int id = -1;
    for (int i = 0; i < n; i++) {
        if (m[i].time == tt) {
            id = i;
            break;
        }
    }
    if (id == -1) {
        return m;
    }
    music* nm = new music[n - 1];
    for (int i = 0, j = 0; i < n; i++) {
        if (i != id) {
            nm[j++] = m[i];
        }
    }
    delete[] m;
    n--;
    return nm;
}

music* add_el(music* m, int& n, int k) {
    int count;
    string br;
    cout << "Сколько песен вы хотите добавить? ";
    getline(cin, br);
    count = stoi(br);
    music* nm = new music[n + count];
    for (int i = 0; i < k; i++) {
        nm[i] = m[i];
    }
    for (int i = 0; i < count; i++) {
        cout << "Песня номер " << i + 1 << " :" << endl;
        nm[k + i] = input();
    }

    for (int i = k; i < n; i++) {
        nm[i + count] = m[i];
    }

    delete[] m;
    n += count;
    return nm;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    fstream fin("8laba.txt");


    int n = 15;
    music* m = new music[n];
    string br;
    int prod;


    for (int i = 0; i < n; i++) {
        getline(fin, br);
        if (br.empty()) {
            getline(fin, br);
        }
        int l1 = br.copy(m[i].naz, 40);
        m[i].naz[l1] = '\0';

        getline(fin, br);
        int l2 = br.copy(m[i].aut, 40);
        m[i].aut[l2] = '\0';

        getline(fin, br);
        m[i].time = stoi(br);
        getline(fin, br);
        m[i].price = stoi(br);
    }
    fin.close();
    string y;
    cout << "Введите длительность удаляемой песни ";
    getline(cin, y);
    prod = stoi(y);

    int c;
    string b;
    cout << "После какой по счёту песни вы хотите добавить свою?";
    getline(cin, b);
    c = stoi(b);
    m = add_el(m, n, c);


    m = del_el(m, n, prod);


    for (int i = 0; i < n; i++) {
        cout << "трек номер: " << i + 1 << endl;
        m[i].nap();
        cout << endl;
    }

    ofstream fout("disks.dat", ios::binary);
    if (fout.is_open()) {
        fout.write((char*)m, n * sizeof(music));
        fout.close();
        cout << "данные сохранены" << endl;
    }

    delete[] m;
    return 0;
}