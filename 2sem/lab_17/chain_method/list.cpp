#include <iostream>
#include "list.h"

void push(List * list, string key, Data data) {
    Node * new_node = new Node;
    new_node->key = key;
    new_node->data = data;

    

    if (list->head == nullptr) {
        list->head = new_node;
        return;
    }
    else {
        Node * cur_node = list->head;
        list->head = new_node;
        new_node->next = cur_node;
    }
}

void del(List * list) {
    if (list->head == nullptr) {
        cout << "List is empty" << endl;
        return;
    }
    Node * temp = list->head;
    if (temp->next == nullptr) {
        delete temp;
        list->head = nullptr;
    }
    else {
        list->head = temp->next;
        delete temp;
    }
}

void clear(List * list) {
    while(list->head != nullptr) {
        del(list);
    } 
}

void print_list(List * list) {
    Node * temp = list->head;
    if (temp == nullptr) {
        cout << "List is empty" << endl;
        return;
    }
    while (temp != nullptr) {
        cout << "[ " << temp->data.name << " " << temp->data.passport_num << " " << temp->key << " ] -> ";
        temp = temp->next;
    }
    cout << endl;
}