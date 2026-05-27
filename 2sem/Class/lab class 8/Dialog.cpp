#include <iostream>
#include "List.h"
#include "Event.h"
#include "Dialog.h"
#include <string>

Dialog::Dialog() : List(), EndState(0) {}
Dialog::~Dialog() {}

void Dialog::GetEvent (TEvent &event) {
    std::string OpInt = "+-?/qam";
    std::string s;
    std::string param;

    char code;

    std::cout << "> ";
    std::cin >> s; 
    code = s[0];

    if (OpInt.find(code) >= 0) {
        event.what = evMessage;
        switch(code) {
            case 'm':
                event.command = cmMake;
                break;

            case '+': 
                event.command = cmAdd;
                break;

            case '-': 
                event.command = cmDel;
                break;

            case '?': 
                event.command = cmShow;
                break;
            
            case '/': 
                event.command = cmGet;
                break; 

            case 'q': 
                event.command = cmQuit;
                break;
        }
        event.a = 0;
        if (s.length() > 1) {
            param = s.substr(1, s.length() - 1);
            int A = atoi(param.c_str());
            event.a = A;
        }
    }
    else event.what = evNothing;
}

int Dialog::Execute() {
    TEvent event;
    do {
        EndState = 0;
        GetEvent(event);
        HandleEvent(event);
    } while(!Valid());

    return EndState;
}

void Dialog::HandleEvent(TEvent &event) {
    if(event.what == evMessage) {
        switch(event.command) {
            case cmMake:
                if (event.a > 0) {
                    size = event.a;
                    delete[] beg;

                    beg = new Object * [size];

                    for (int i = 0; i < size; i++) {
                        beg[i] = nullptr;
                    }
                }
                else {
                    delete[] beg;
                    beg = nullptr;
                }
                
                ClearEvent(event);
                break;

            case cmAdd:
                Add();
                ClearEvent(event);
                break;

            case cmDel:
                Del();
                ClearEvent(event);
                break;

            case cmShow:
                Show();
                ClearEvent(event);
                break;

            case cmQuit:
                EndExec();
                ClearEvent(event);
                break;

            default:
                List::HandleEvent(event);
        }
    }
}


void Dialog::ClearEvent (TEvent &event) {
    event. what = evNothing;
}

int Dialog::Valid() {
    if (EndState == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

void Dialog::EndExec() {
    EndState = 1;
}