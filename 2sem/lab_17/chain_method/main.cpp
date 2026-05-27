#include <iostream>
#include <string>
#include <cmath>
#include "list.h"

using namespace std;

struct HashTable {
    int size;
    List ** table;

    HashTable(int size) : size(size) {
        table = new List*[size];

        for (int i = 0; i < size; i++) {
            table[i] = new List;
        }
        cout << "Table created" << endl;
    }

    int hash(string key, const double A = 0.54321) {
        int res = size * fmod(((double)key.size() * A), 1.0);
        return res;
    }

    void insert(string address, Data value) {        
        if (table == nullptr) {
            table = new List*[size];

            for (int i = 0; i < size; i++) {
                table[i] = new List;
            }
            cout << "Table created" << endl;
        }

        if (search(address).name != "") {
            update(address, value);
            return;
        }

        int idx = hash(address);

        if (table[idx]->head == nullptr) {
            table[idx]->head = new Node;
            table[idx]->head->key = address;
            table[idx]->head->data = value;
        }
        else {
            push(table[idx], address, value);
        }
    }

    void update(string address, Data value) {
        int idx = hash(address);
        Node * cur_node = table[idx]->head;

        while (cur_node->key != address) {
            cur_node = cur_node->next;
        }
        cur_node->data = value;
        cout << "Data updated" << endl;
    }

    Data search(string key) {
        if (table == nullptr) {
            cout << "Table is empty" << endl;
            return Data();
        }

        int idx = hash(key);
        Node * cur_node = table[idx]->head; 

        while (cur_node != nullptr) {
            if (key == cur_node->key) {
                cout << "Data found" << endl;
                return cur_node->data;
            }
            cur_node = cur_node->next;
        }
        cout << "Nothing found" << endl;
        return Data();
    }

    void del_elem(string key) {
        if (table == nullptr) {
            cout << "Table is empty" << endl;
            return;
        }

        int idx = hash(key);
        
        if (table[idx] == nullptr || table[idx]->head == nullptr) {
            cout << "Nothing deleted!" << endl;
            return;
        }

        Node * head = table[idx]->head;
        
        if (head->key == key) {
            table[idx]->head = head->next;
            delete head;
            cout << "Elem deleted" << endl;
            return;
        }
        
        Node * prev = head;
        Node * cur = head->next;
        while (cur) {
            if (cur->key == key) {
                prev->next = cur->next;
                delete cur;
                cout << "Elem deleted" << endl;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
        cout << "Nothing deleted" << endl;
    }

    void clear_table() {
        if (table == nullptr) {
            cout << "Table is empty" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            if (table[i]->head != nullptr) {
                clear(table[i]);
                delete table[i];
            }
        }
        delete[] table;
        table = nullptr;
        cout << "Table deleted" << endl;
    }

    void print_table() {
        if (table == nullptr) {
            cout << "Table is empty" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << i << " ";
            print_list(table[i]);
        }
    }
};

int main() {
    HashTable a = {10};
    a.print_table();
    Data s1 = {"Piter", 123};
    Data s2 = {"Pit", 234};
    Data s3 = {"Pet", 345};
    Data s4 = {"Nik", 456};

    a.insert("Lenina", s1);
    a.insert("Bolshevitskia", s3);
    a.insert("Kirovskia", s4);
    a.insert("Bebrina", s5);

    a.search("Lenina");
    a.search("Bebrina");

    a.print_table();
    a.insert("Lenina", s2);
    a.print_table();
    a.del_elem("Lenina");
    a.print_table();

    a.clear_table();
    a.print_table();

    return 0;
}