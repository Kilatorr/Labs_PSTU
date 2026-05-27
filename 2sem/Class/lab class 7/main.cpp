#include <iostream>
#include "Set.h"
#include "Money.h"

int main() {
    Set<Money> set(2);
    std::cin >> set;
    std::cout << set << std::endl;

    std::cout << set[1] << std::endl;

    try {
        std::cout << set[10] << std::endl;
    }
    catch (std::out_of_range &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    Money a(200, 0);
    set[0] = a;
    std::cout << set << std::endl;
    Set<Money> new_set(3);
    std::cin >> new_set;

    Set<Money> c = set + new_set;
    std::cout << c << std::endl;

    return 0;
}