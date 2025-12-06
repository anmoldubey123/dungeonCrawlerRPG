// tests/test_monster_base.cpp
#include <iostream>
#include <vector>
#include "Monster.h"
#include "Item.h"

int main() {
    Monster orc("Orc", 50, 8, 3, 20, 10);

    std::cout << "=== Orc Created ===" << std::endl;
    orc.displayStats();

    std::cout << "\n=== Adding Loot ===" << std::endl;
    orc.addLoot(new Consumable("Potion", "Heals", 15));

    std::cout << "\n=== Orc Takes Damage ===" << std::endl;
    orc.takeDamage(30);  // reuse Character::takeDamage

    std::cout << "\n=== Dropping Loot ===" << std::endl;
    std::vector<Item*> loot = orc.dropLoot();

    std::cout << "Loot dropped: " << loot.size() << " item(s)" << std::endl;
    for (std::size_t i = 0; i < loot.size(); ++i) {
        loot[i]->displayInfo();
    }

    // Clean up loot (caller now owns it!)
    for (std::size_t i = 0; i < loot.size(); ++i) {
        delete loot[i];
    }
    loot.clear();

    std::cout << "\n=== Test Complete ===" << std::endl;
    return 0;
}
