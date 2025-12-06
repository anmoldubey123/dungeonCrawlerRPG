#include <iostream>
#include "Item.h"   // This declares Item, Weapon, Armor, Consumable

int main() {
    Weapon sword("Iron Sword", "A sturdy blade", 5);

    std::cout << "=== Direct call ===" << std::endl;
    sword.displayInfo();

    std::cout << "\n=== Polymorphic call through Item* ===" << std::endl;
    Item* item_ptr = &sword;
    item_ptr->displayInfo();   // Should call Weapon::displayInfo()

    return 0;
}
