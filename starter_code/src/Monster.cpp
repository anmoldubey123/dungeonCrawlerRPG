#include "Monster.h"
#include <iostream>

// ============================================================================
// Base Monster class
// ============================================================================

// TODO: Implement Monster constructor
// HINTS:
// - MUST call Character base constructor
// - Initialize experience_reward and gold_reward
// - Loot table starts empty automatically
//
Monster::Monster(const std::string& name, int hp, int attack, int defense,
                 int exp_reward, int gold_reward)
    : Character(name, hp, attack, defense),
      experience_reward(exp_reward), gold_reward(gold_reward) {
}


// TODO: Implement Monster destructor
// HINTS:
// - Deallocate any allocated memory 
// - Loop through loot_table vector and delete each Item*
// - Clear the vector after deleting items
//
Monster::~Monster() {
    for (std::size_t i = 0; i < loot_table.size(); ++i) {
        delete loot_table[i];   // free allocated loot items
    }
    loot_table.clear();         // remove dangling pointers
}



// TODO: Override displayStats
// HINTS:
// - Show monster name and HP
// - Format: "MonsterName [HP: current/max]"
// - Keep it simple - monsters don't need detailed stats display
//
void Monster::displayStats() const {
    std::cout << getName() 
              << " [HP: " << getCurrentHP()
              << "/" << getMaxHP() << "]" 
              << std::endl;
}



// TODO: Implement addLoot
// HINTS:
// - Check if item pointer is not NULL
// - Add item to loot_table vector using push_back()
//
void Monster::addLoot(Item* item) {
    if (item == NULL) {
        std::cout << "Cannot add NULL loot item." << std::endl;
        return;
    }
    loot_table.push_back(item);
}



// TODO: Implement dropLoot
// HINTS:
// - Create a copy of the loot_table vector
// - Clear the original loot_table (transfer ownership to caller!)
// - Return the copy
// - This is important: caller now owns the items and must delete them
//
std::vector<Item*> Monster::dropLoot() {
    // Copy current loot for caller
    std::vector<Item*> dropped = loot_table;

    // Clear internal loot so Monster no longer owns items
    loot_table.clear();

    // Caller is now responsible for deleting items later!
    return dropped;
}



// TODO: Implement getAttackMessage (base version)
// HINTS:
// - Return default attack message
// - Format: "MonsterName attacks!"
// - Use getName() to get monster's name
//
std::string Monster::getAttackMessage() const {
    return getName() + " attacks!";
}



// ============================================================================
// Goblin - Weak but common enemy
// ============================================================================

// TODO: Implement Goblin constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Goblin"
//   * HP: 30
//   * Attack: 5
//   * Defense: 2
//   * Experience: 10
//   * Gold: 5
// - Add a small potion to loot table
// - Example: addLoot(new Consumable("Small Potion", "Restores 10 HP", 10));
//
Goblin::Goblin()
    : Monster("Goblin", 30, 5, 2, 10, 5)
{
    addLoot(new Consumable("Small Potion", "Restores 10 HP", 10));
}



// TODO: Override getAttackMessage for Goblin
// HINTS:
// - Return goblin-specific attack message
// - Example: "The goblin swipes at you with its rusty dagger!"
//
std::string Goblin::getAttackMessage() const {
    return "The goblin swipes at you with its rusty dagger!";
}



// ============================================================================
// Skeleton - Undead warrior
// ============================================================================

// TODO: Implement Skeleton constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Skeleton"
//   * HP: 40
//   * Attack: 8
//   * Defense: 4
//   * Experience: 20
//   * Gold: 10
// - Add an old sword to loot table
//
Skeleton::Skeleton()
    : Monster("Skeleton", 40, 8, 4, 20, 10)
{
    addLoot(new Weapon("Old Sword", "A worn but sharp blade", 3));
}



// TODO: Override getAttackMessage for Skeleton
// HINTS:
// - Return skeleton-specific attack message
// - Example: "The skeleton rattles its bones and slashes with a sword!"
//
std::string Skeleton::getAttackMessage() const {
    return "The skeleton rattles its bones and slashes with a sword!";
}



// ============================================================================
// Dragon - Boss enemy with special ability
// ============================================================================

// TODO: Implement Dragon constructor
// HINTS:
// - Call Monster constructor with these stats:
//   * Name: "Dragon"
//   * HP: 150
//   * Attack: 20
//   * Defense: 10
//   * Experience: 100
//   * Gold: 50
// - Add legendary loot:
//   * Dragon Slayer sword (damage +10)
//   * Dragon Scale Armor (defense +8)
//   * Greater Health Potion (heals 100 HP)
//
Dragon::Dragon()
    : Monster("Dragon", 150, 20, 10, 100, 50)
{
    addLoot(new Weapon("Dragon Slayer", "A legendary blade", 10));
    addLoot(new Armor("Dragon Scale Armor", "Armor made from dragon scales", 8));
    addLoot(new Consumable("Greater Potion", "Restores a huge amount of HP", 100));
}



// TODO: Override getAttackMessage for Dragon
// HINTS:
// - Return dragon-specific attack message
// - Example: "The dragon breathes fire at you!"
//
std::string Dragon::getAttackMessage() const {
    return "The dragon breathes fire at you!";
}



// TODO: Override calculateDamage for Dragon
// HINTS:
// - Call Monster::calculateDamage() to get base damage
// - Add bonus fire damage (+5)
// - Return total damage
// - This makes the dragon hit harder than other monsters!
//
int Dragon::calculateDamage() const {
    int base = Monster::calculateDamage();  // Base monster damage with randomness
    return base + 5; // Fire damage bonus
}

