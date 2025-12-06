// tests/test_consumable.cpp
#include <iostream>
#include "Item.h"   // Contains Item, Weapon, Armor, Consumable

int main() {
    Consumable potion("Health Potion", "Restores health", 30);

    std::cout << "=== Consumable Display Test ===" << std::endl;
    potion.displayInfo();

    std::cout << "\n=== First Use ===" << std::endl;
    potion.use();      // Should work, mark item as used

    std::cout << "\n=== Second Use (Should Fail) ===" << std::endl;
    potion.use();      // Should print an error message

    return 0;
}
