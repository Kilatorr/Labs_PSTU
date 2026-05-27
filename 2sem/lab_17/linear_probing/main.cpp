#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Data {
    string address = "";
    string name = "";
    int passport_num = 0;
    bool isDel = false;

    bool isEmpty() {
        return (!isDel && address == "");
    }
};

struct HashTable {
    int size;
    int count;
    Data * table;
    
    HashTable(int size) : size(size) {
        count = 0;
        table = new Data[size];
        cout << "Table created" << endl;
    }

    int hash(string key, const double A = 0.54321) {
        int res = size * fmod(((double)key.size() * A), 1.0);
        return res;
    }

    void insert(Data data) {       
        if (size == count) {
            cout << "Table is full!" << endl;
            return;
        } 
        int start_idx = hash(data.address);
        int idx = start_idx;

        while(!table[idx].isEmpty() && !table[idx].isDel) {
            if (data.address == table[idx].address) {
                table[idx] = data;
                cout << "Data updated" << endl;
                return; 
            } 
            idx = (idx + 1) % size;
        }

        table[idx] = data;
        cout << "Data inserted" << endl;
        count++;
    }

    void search(string address) {
        int start_idx = hash(address);
        int idx = start_idx;

        while(!table[idx].isEmpty()) {
            if (!table[idx].isDel && table[idx].address == address) {
                cout << "Find: " << table[idx].name << " " << table[idx].passport_num << endl;
                return;
            }
            idx = (idx + 1) % size;

            if (idx == start_idx) {
                cout << "Nothing found" << endl;
                break;
            }
        }
    }

    void del_elem(string address) {
        int start_idx = hash(address);
        int idx = start_idx;
        
        while(!table[idx].isEmpty()) {
            if (!table[idx].isDel && table[idx].address == address) {
                table[idx].isDel = true;
                count--;
                cout << "Elem deleted" << endl;
                return;
            }
            idx = (idx + 1) % size;

            if (idx == start_idx) {
                cout << "Nothing deeted" << endl;
                break;
            }
        }
    }

    void clear_table() {
        delete[] table;
        table = new Data[size];
        count = 0;
        cout << "Table deleted" << endl;
    }

    void print_table() {
        if (count == 0) {
            cout << "Table is empty" << endl;
            return;
        }

        for (int i = 0; i < size; i++) {
            cout << i << " ";
            if (!table[i].isEmpty()) {
                cout << table[i].name << " " << table[i].passport_num << endl;
            }
            else {
                cout << "Nothing" << endl;
            }
        }
    }
};

int main() {
    HashTable a = {10};
    a.print_table();
    Data s1 = {"Lenina", "Piter", 123};
    Data s2 = {"Bolshevitskia", "Pit", 234};
    Data s3 = {"Kirovskia", "Pet", 345};
    Data s4 = {"Lenina", "Pony", 755};

    a.insert(s1);
    a.insert(s2);
    a.insert(s3);
    

    a.search("Lenina");
    a.search("Bebrina");

    a.print_table();
    a.del_elem("Lenina");
    a.insert(s4);
    a.print_table();

    a.clear_table();
    a.print_table();

    return 0;
}