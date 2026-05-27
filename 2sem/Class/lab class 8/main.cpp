#include <iostream>
#include "Object.h"
#include "Person.h"
#include "Student.h"
#include "List.h"
#include "Dialog.h"

int main() {
    Dialog D;
    D.Execute();
    std::cout << "Ok" << std::endl;

    return 0;
}