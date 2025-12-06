// tests/test_inventory.cpp
#include <iostream>
#include <vector>
#include <string>
#include "Item.h"   // Contains Item, Weapon, Armor, Consumable

int main() {

    std::vector<Item*> inventory;

    // Add items dynamically
    inventory.push_back(new Weapon("Sword", "Sharp blade", 5));
    inventory.push_back(new Armor("Shield", "Wooden shield", 2));
    inventory.push_back(new Consumable("Potion", "Restores health", 20));
    inventory.push_back(new Armor("Helmet", "Protects your head", 1));

    std::cout << "=== INVENTORY CONTENTS ===" << std::endl;
    for (Item* item : inventory) {
        item->displayInfo();
        std::cout << std::endl;
    }

    // -----------------------------
    // Remove an item by name
    // -----------------------------
    std::string nameToRemove = "Shield";
    std::cout << "Removing: " << nameToRemove << std::endl;

    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == nameToRemove) {
            delete *it;         // free memory!
            inventory.erase(it); // remove from vector
            break;
        }
    }

    std::cout << "\n=== INVENTORY AFTER REMOVAL ===" << std::endl;
    for (Item* item : inventory) {
        item->displayInfo();
        std::cout << std::endl;
    }

    // -----------------------------
    // VERY IMPORTANT: delete all items
    // -----------------------------
    for (Item* item : inventory) {
        delete item;
    }
    inventory.clear();

    return 0;
}
