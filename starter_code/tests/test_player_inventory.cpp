// tests/test_player_inventory.cpp
#include <iostream>
#include "Player.h"
#include "Item.h"

int main() {
    Player hero("Bob");

    std::cout << "=== Adding Items ===" << std::endl;
    hero.addItem(new Weapon("Sword", "Sharp", 5));
    hero.addItem(new Consumable("Potion", "Heals", 20));

    std::cout << "\n=== Inventory After Adding ===" << std::endl;
    hero.displayInventory();

    std::cout << "\nHas 'Potion'? " 
              << (hero.hasItem("Potion") ? "yes" : "no") << std::endl;
    std::cout << "Has 'potion'? " 
              << (hero.hasItem("potion") ? "yes" : "no") << std::endl;

    std::cout << "\n=== Removing 'potion' (case-insensitive) ===" << std::endl;
    hero.removeItem("potion");   // should remove "Potion"

    std::cout << "\n=== Inventory After Removing Potion ===" << std::endl;
    hero.displayInventory();

    std::cout << "\nHas 'Potion'? " 
              << (hero.hasItem("Potion") ? "yes" : "no") << std::endl;

    return 0;
}
