#include "Player.h"
#include <iostream>
#include <algorithm>

// TODO: Implement Player constructor
// HINTS:
// - MUST call Character base constructor. 
//
Player::Player(const std::string& name)
    : Character(name, 100, 10, 5),
      level(1), experience(0), gold(0),
      equipped_weapon(NULL), equipped_armor(NULL) {
}


// TODO: Implement Player destructor
// HINTS:
// - CRITICAL: Must delete all items in inventor    y to prevent memory leaks!
// - DON'T delete equipped_weapon or equipped_armor - they point to items
//   already in the inventory, so they're already deleted!
//
Player::~Player() {
    // Delete all items that the player owns
    for (std::size_t i = 0; i < inventory.size(); ++i) {
        delete inventory[i];
    }
    
    // Clear the vector to remove dangling pointers
    inventory.clear();
}



// TODO: Override displayStats
// HINTS:
// - Show player-specific information
// - Include: level, HP, attack (with weapon bonus), defense (with armor bonus), gold, experience
// - Show equipped weapon and armor names if any
// - Use decorative formatting (borders, headers)
// - Use getters to access inherited Character data
//
void Player::displayStats() const {
    int base_attack  = getAttack();
    int base_defense = getDefense();
    int weapon_bonus = 0;
    int armor_bonus  = 0;
    
    std::string weapon_name = "None";
    std::string armor_name  = "None";

    // If a weapon is equipped, use its value as bonus
    if (equipped_weapon != NULL) {
        weapon_bonus = equipped_weapon->getValue();
        weapon_name  = equipped_weapon->getName();
    }

    // If armor is equipped, use its value as bonus
    if (equipped_armor != NULL) {
        armor_bonus = equipped_armor->getValue();
        armor_name  = equipped_armor->getName();
    }

    int total_attack  = base_attack  + weapon_bonus;
    int total_defense = base_defense + armor_bonus;

    std::cout << "==============================\n";
    std::cout << "      PLAYER STATS\n";
    std::cout << "==============================\n";
    std::cout << "Name : " << getName() << "\n";
    std::cout << "Level: " << level 
              << "    EXP: " << experience << "\n";
    std::cout << "HP   : " << getCurrentHP() << "/" << getMaxHP() << "\n";

    std::cout << "ATK  : " << base_attack;
    if (weapon_bonus != 0) {
        std::cout << " (+" << weapon_bonus << ") = " << total_attack;
    }
    std::cout << "\n";

    std::cout << "DEF  : " << base_defense;
    if (armor_bonus != 0) {
        std::cout << " (+" << armor_bonus << ") = " << total_defense;
    }
    std::cout << "\n";

    std::cout << "Gold : " << gold << "\n";

    std::cout << "Weapon: " << weapon_name;
    if (weapon_bonus != 0) {
        std::cout << " (+" << weapon_bonus << " ATK)";
    }
    std::cout << "\n";

    std::cout << "Armor : " << armor_name;
    if (armor_bonus != 0) {
        std::cout << " (+" << armor_bonus << " DEF)";
    }
    std::cout << "\n";

    std::cout << "==============================\n";
}



// TODO: Override calculateDamage to include weapon bonus
// HINTS:
// - If weapon is equipped, add weapon's damage bonus
// - Return total damage
//
int Player::calculateDamage() const {
    // Get base damage from Character (includes randomness)
    int base_damage = Character::calculateDamage();

    int weapon_bonus = 0;

    // If a weapon is equipped and it's actually a Weapon, add its value
    if (equipped_weapon != NULL && equipped_weapon->getType() == "Weapon") {
        weapon_bonus = equipped_weapon->getValue();
    }

    return base_damage + weapon_bonus;
}




// TODO: Implement addItem
// HINTS:
// - Add item to inventory vector using push_back()
// - Print pickup message with item name
//
void Player::addItem(Item* item) {
    if (item == NULL) {
        std::cout << "Cannot add NULL item to inventory!" << std::endl;
        return;
    }

    inventory.push_back(item);

    std::cout << "Picked up: " << item->getName()
              << " (" << item->getType() << ")" << std::endl;
}



// TODO: Implement removeItem
// HINTS:
// - Search inventory for item by name (case-insensitive comparison)
// - If found: delete the item, then erase from vector
// - If not found: print error message
// - Remember: inventory.erase(inventory.begin() + i) to remove at index i
//
void Player::removeItem(const std::string& item_name) {
    if (inventory.empty()) {
        std::cout << "Inventory is empty!" << std::endl;
        return;
    }

    // Convert target name to lowercase for comparison
    std::string lower_target = item_name;
    std::transform(lower_target.begin(), lower_target.end(),
                   lower_target.begin(), ::tolower);

    for (std::size_t i = 0; i < inventory.size(); ++i) {

        // Convert this item's name to lowercase
        std::string lower_item = inventory[i]->getName();
        std::transform(lower_item.begin(), lower_item.end(),
                       lower_item.begin(), ::tolower);

        if (lower_item == lower_target) {
            std::cout << "Removed: " << inventory[i]->getName() << std::endl;

            delete inventory[i];               // free memory
            inventory.erase(inventory.begin() + i);  // remove from vector
            return;
        }
    }

    std::cout << "Item not found: " << item_name << std::endl;
}



// TODO: Implement displayInventory
// HINTS:
// - Print header: "----- Inventory -----"
// - If inventory is empty, print "Empty"
// - Otherwise, loop through and print each item's name and type
// - Format: "- ItemName (ItemType)"
// - Print footer: "--------------------"
//
void Player::displayInventory() const {
    std::cout << "----- Inventory -----" << std::endl;

    if (inventory.empty()) {
        std::cout << "Empty" << std::endl;
        std::cout << "---------------------" << std::endl;
        return;
    }

    for (std::size_t i = 0; i < inventory.size(); ++i) {
        std::cout << "- " << inventory[i]->getName()
                  << " (" << inventory[i]->getType() << ")" << std::endl;
    }

    std::cout << "---------------------" << std::endl;
}



// TODO: Implement hasItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return true if found, false otherwise
// - Use same case-insensitive comparison as removeItem
//
bool Player::hasItem(const std::string& item_name) const {
    std::string lower_target = item_name;
    std::transform(lower_target.begin(), lower_target.end(),
                   lower_target.begin(), ::tolower);

    for (std::size_t i = 0; i < inventory.size(); ++i) {
        std::string lower_item = inventory[i]->getName();
        std::transform(lower_item.begin(), lower_item.end(),
                       lower_item.begin(), ::tolower);

        if (lower_item == lower_target) {
            return true;
        }
    }

    return false;
}



// TODO: Implement getItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return pointer to item if found
// - Return NULL if not found
//
Item* Player::getItem(const std::string& item_name) {
    std::string lower_target = item_name;
    std::transform(lower_target.begin(), lower_target.end(),
                   lower_target.begin(), ::tolower);

    for (std::size_t i = 0; i < inventory.size(); ++i) {
        std::string lower_item = inventory[i]->getName();
        std::transform(lower_item.begin(), lower_item.end(),
                       lower_item.begin(), ::tolower);

        if (lower_item == lower_target) {
            return inventory[i];
        }
    }

    return NULL;
}



// TODO: Implement equipWeapon
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Weapon"
// - If current weapon equipped, print unequip message
// - Set equipped_weapon pointer to this item
// - Print equip message
//
void Player::equipWeapon(const std::string& weapon_name) {
    // Find the item in inventory (case-insensitive via getItem)
    Item* item = getItem(weapon_name);

    if (item == NULL) {
        std::cout << "Cannot equip weapon: item \"" 
                  << weapon_name << "\" not found in inventory." << std::endl;
        return;
    }

    if (item->getType() != "Weapon") {
        std::cout << "Cannot equip \"" << item->getName() 
                  << "\": not a weapon." << std::endl;
        return;
    }

    if (equipped_weapon != NULL) {
        std::cout << "Unequipped weapon: " << equipped_weapon->getName() << std::endl;
    }

    equipped_weapon = item;

    std::cout << "Equipped weapon: " << item->getName() << std::endl;
}



// TODO: Implement equipArmor
// HINTS:
// - Similar to equipWeapon but for armor
// - Check if item type is "Armor"
// - Set equipped_armor pointer
//
void Player::equipArmor(const std::string& armor_name) {
    // Find the item in inventory
    Item* item = getItem(armor_name);

    if (item == NULL) {
        std::cout << "Cannot equip armor: item \"" 
                  << armor_name << "\" not found in inventory." << std::endl;
        return;
    }

    if (item->getType() != "Armor") {
        std::cout << "Cannot equip \"" << item->getName() 
                  << "\": not armor." << std::endl;
        return;
    }

    if (equipped_armor != NULL) {
        std::cout << "Unequipped armor: " << equipped_armor->getName() << std::endl;
    }

    equipped_armor = item;

    std::cout << "Equipped armor: " << item->getName() << std::endl;
}



// TODO: Implement unequipWeapon
// HINTS:
// - Check if weapon is currently equipped
// - If so, print message and set equipped_weapon to NULL
// - If not, print error message
//
void Player::unequipWeapon() {
    if (equipped_weapon == NULL) {
        std::cout << "No weapon is currently equipped." << std::endl;
        return;
    }

    std::cout << "Unequipped weapon: " << equipped_weapon->getName() << std::endl;
    equipped_weapon = NULL;
}



// TODO: Implement unequipArmor
// HINTS:
// - Similar to unequipWeapon
// - Set equipped_armor to NULL
//
void Player::unequipArmor() {
    if (equipped_armor == NULL) {
        std::cout << "No armor is currently equipped." << std::endl;
        return;
    }

    std::cout << "Unequipped armor: " << equipped_armor->getName() << std::endl;
    equipped_armor = NULL;
}



// TODO: Implement useItem
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Consumable"
// - Cast to Consumable*: Consumable* consumable = static_cast<Consumable*>(item)
// - Check if already used: consumable->isUsed()
// - Get healing amount: consumable->getHealingAmount()
// - Call heal() with that amount
// - Call consumable->use() to mark as used
// - Remove item from inventory (it's been consumed!)
//
void Player::useItem(const std::string& item_name) {
    // Find the item in inventory
    Item* item = getItem(item_name);

    if (item == NULL) {
        std::cout << "Cannot use item: \"" << item_name 
                  << "\" not found in inventory." << std::endl;
        return;
    }

    if (item->getType() != "Consumable") {
        std::cout << "Cannot use \"" << item->getName() 
                  << "\": not a consumable item." << std::endl;
        return;
    }

    // Safe to cast now because we checked type
    Consumable* consumable = static_cast<Consumable*>(item);

    if (consumable->isUsed()) {
        std::cout << "Cannot use \"" << consumable->getName() 
                  << "\": item has already been used." << std::endl;
        return;
    }

    int healing_amount = consumable->getHealingAmount();

    // Heal the player using Character::heal()
    heal(healing_amount);

    // Mark consumable as used & print its message
    consumable->use();

    // Remove the item from inventory (it's been consumed)
    removeItem(item->getName());
}


// TODO: Implement gainExperience
// HINTS:
// - Add experience points
// - Print message showing exp gained
// - Check if enough exp to level up: if (experience >= level * 100)
// - If so, call levelUp()
//
void Player::gainExperience(int exp) {
    if (exp <= 0) {
        std::cout << getName() << " gains no experience." << std::endl;
        return;
    }

    experience += exp;

    std::cout << getName() << " gains " << exp 
              << " EXP! (Total: " << experience << ")" << std::endl;

    // Check if enough experience to level up
    if (experience >= level * 100) {
        levelUp();
    }
}



// TODO: Implement levelUp
// HINTS:
// - Increment level
// - Reset experience to 0
// - Increase stats:
//   * Increase max_hp by 10 (use setMaxHP())
//   * Set current_hp to max (full heal on level up)
//   * Increase attack by 2
//   * Increase defense by 1
// - Print celebratory level up message
// - Display new stats
//
void Player::levelUp() {
    level++;

    // Reset experience after leveling up
    experience = 0;

    // Increase stats
    int new_max_hp = getMaxHP() + 10;
    setMaxHP(new_max_hp);
    setCurrentHP(new_max_hp);          // full heal on level up

    setAttack(getAttack() + 2);
    setDefense(getDefense() + 1);

    std::cout << "\n=== LEVEL UP! ===" << std::endl;
    std::cout << getName() << " reached level " << level << "!" << std::endl;

    // Show the new stats
    displayStats();
}

