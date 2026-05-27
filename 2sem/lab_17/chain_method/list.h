#include <string>
#pragma once

using namespace std;

struct Data {
    string name = "";
    int passport_num = 0;
};

struct Node {
    string key;
    Data data;
    Node * next = nullptr;
};

struct List {
    Node * head = nullptr;
};

void push(List * list, string addres, Data data);
void del(List * list);
void clear(List * list);
void print_list(List * list);