// tests/test_player_equipment.cpp
#include <iostream>
#include "Player.h"
#include "Item.h"

int main() {
    Player hero("Charlie");

    std::cout << "\n=== Adding Items ===" << std::endl;
    hero.addItem(new Weapon("Sword", "Sharp", 5));
    hero.addItem(new Armor("Chainmail", "Strong", 3));

    std::cout << "\n=== Equipping Items (case-insensitive) ===" << std::endl;
    hero.equipWeapon("sword");       // lower-case on purpose
    hero.equipArmor("chainmail");

    std::cout << "\n=== Player Stats After Equipping ===" << std::endl;
    hero.displayStats();

    std::cout << "\n=== Damage Calculation ===" << std::endl;
    int dmg = hero.calculateDamage();
    std::cout << "Damage dealt: " << dmg << std::endl;

    return 0;
}
