#include <iostream>
#include "Item.h"

int main() {
    Item sword("Iron Sword", "A sturdy blade", "Weapon", 5);
    sword.displayInfo();
    std::cout << std::endl << "Brief: ";
    sword.displayBrief();
    std::cout << std::endl;
    return 0;
}
