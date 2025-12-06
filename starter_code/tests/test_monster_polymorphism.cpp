// tests/test_monster_polymorphism.cpp
#include <iostream>
#include "Monster.h"
#include "Item.h"

int main() {
    // Test polymorphism - base class pointers to derived objects
    Monster* monsters[3];
    monsters[0] = new Goblin();
    monsters[1] = new Skeleton();
    monsters[2] = new Dragon();
    
    for (int i = 0; i < 3; i++) {
        monsters[i]->displayStats();
        std::cout << monsters[i]->getAttackMessage() << std::endl;
        int dmg = monsters[i]->calculateDamage();
        std::cout << "Damage: " << dmg << std::endl;
        std::cout << std::endl;
    }
    
    // Clean up
    for (int i = 0; i < 3; i++) {
        delete monsters[i];   // Calls virtual destructors & frees loot
    }
    
    return 0;
}
