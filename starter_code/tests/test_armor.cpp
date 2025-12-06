// tests/test_armor.cpp
#include <iostream>
#include "Item.h"   // Contains Armor, Weapon, Consumable, Item

int main() {
    Armor chainmail("Chain Mail", "Protective armor", 3);

    std::cout << "=== Armor Display Test ===" << std::endl;
    chainmail.displayInfo();

    std::cout << "\n=== Brief Info Test ===" << std::endl;
    chainmail.displayBrief();   // should print: Chain Mail (Armor)
    std::cout << std::endl;

    return 0;
}
