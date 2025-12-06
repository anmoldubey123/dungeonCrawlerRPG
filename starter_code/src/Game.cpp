#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// TODO: Implement Game constructor
Game::Game() : player(NULL), current_room(NULL), 
               game_over(false), victory(false) {
}


// TODO: Implement Game destructor
Game::~Game() {
    // Delete player if it exists
    if (player != NULL) {
        delete player;
        player = NULL;
    }

    // Delete all rooms in the world map
    for (std::map<std::string, Room*>::iterator it = world.begin();
         it != world.end(); ++it) {
        delete it->second;
    }
    world.clear();
}



// TODO: Implement initializeWorld
// HINTS:
// - Create all rooms with new
// - Add each room to world using addRoom()
// - Connect rooms using connectRooms()
// - Add monsters to appropriate rooms using room->setMonster()
// - Add items to rooms using room->addItem()
// - Set current_room to starting room (entrance)
//
// SUGGESTED WORLD LAYOUT:
//                [Throne Room]
//                     |
//     [Armory] - [Hallway] - [Treasury]
//                     |
//                 [Entrance]
//
// MONSTERS:
// - Hallway: Goblin
// - Armory: Skeleton
// - Treasury: Skeleton
// - Throne Room: Dragon (boss!)
//
// ITEMS:
// - Entrance: Small Potion
// - Armory: Iron Sword, Chain Mail
// - Treasury: Health Potion
//
void Game::initializeWorld() {
    // ===== Create rooms =====
    Room* entrance   = new Room("Entrance",   "You stand at the entrance of a dark dungeon.");
    Room* hallway    = new Room("Hallway",    "A narrow stone hallway lined with old torches.");
    Room* armory     = new Room("Armory",     "Weapons and armor are scattered everywhere.");
    Room* treasury   = new Room("Treasury",   "Piles of old coins and chests fill the room.");
    Room* throneRoom = new Room("Throne Room","A grand chamber with a towering throne.");

    // ===== Add rooms to world =====
    addRoom(entrance);
    addRoom(hallway);
    addRoom(armory);
    addRoom(treasury);
    addRoom(throneRoom);

    // ===== Connect rooms bidirectionally =====
    // Entrance <-> Hallway
    connectRooms("Entrance", "north", "Hallway");

    // Hallway <-> Armory
    connectRooms("Hallway", "west", "Armory");

    // Hallway <-> Treasury
    connectRooms("Hallway", "east", "Treasury");

    // Hallway <-> Throne Room
    connectRooms("Hallway", "north", "Throne Room");

    // ===== Add monsters =====
    // Hallway: Goblin
    hallway->setMonster(new Goblin());

    // Armory: Skeleton
    armory->setMonster(new Skeleton());

    // Treasury: Skeleton
    treasury->setMonster(new Skeleton());

    // Throne Room: Dragon (boss)
    throneRoom->setMonster(new Dragon());

    // ===== Add items =====
    // Entrance: Small Potion
    entrance->addItem(new Consumable("Small Potion", "Restores 10 HP", 10));

    // Armory: Iron Sword, Chain Mail
    armory->addItem(new Weapon("Iron Sword", "A well-balanced steel sword.", 5));
    armory->addItem(new Armor("Chain Mail", "Sturdy chain mail armor.", 4));

    // Treasury: Health Potion
    treasury->addItem(new Consumable("Health Potion", "Restores 30 HP", 30));

    // ===== Set starting room =====
    current_room = entrance;
}



// TODO: Implement createStartingInventory
// HINTS:
// - Give player starting weapon: Rusty Dagger (damage +2)
// - Give player starting food: Bread (heals 5 HP)
// - Use: player->addItem(new Weapon(...))
//
void Game::createStartingInventory() {
    if (player == NULL) {
        std::cout << "Error: player is NULL in createStartingInventory()." << std::endl;
        return;
    }

    // Starting weapon: Rusty Dagger (+2 damage)
    player->addItem(new Weapon("Rusty Dagger", "An old but still sharp dagger.", 2));

    // Starting food: Bread (+5 HP)
    player->addItem(new Consumable("Bread", "A simple loaf of bread. Restores a little HP.", 5));
}



// TODO: Implement addRoom
// HINTS:
// - Check if room pointer is not NULL
// - Add to world map using room's name as key
// - Use: world[room->getName()] = room
//
void Game::addRoom(Room* room) {
    if (room == NULL) {
        std::cout << "Cannot add NULL room to world!" << std::endl;
        return;
    }
    world[room->getName()] = room;
}



// TODO: Implement connectRooms
// HINTS:
// - Look up both rooms in world map
// - If both exist:
//   - Add forward direction: room1->addExit(direction, room2)
//   - Determine reverse direction:
//     * north ↔ south
//     * east ↔ west
//   - Add reverse direction: room2->addExit(reverse, room1)
//
void Game::connectRooms(const std::string& room1_name, const std::string& direction,
                        const std::string& room2_name) {
    // Look up both rooms in the world map
    std::map<std::string, Room*>::iterator it1 = world.find(room1_name);
    std::map<std::string, Room*>::iterator it2 = world.find(room2_name);

    if (it1 == world.end() || it2 == world.end()) {
        std::cout << "Error: cannot connect rooms \"" << room1_name
                  << "\" and \"" << room2_name << "\" (one or both not found)"
                  << std::endl;
        return;
    }

    Room* room1 = it1->second;
    Room* room2 = it2->second;

    // Add forward direction
    room1->addExit(direction, room2);

    // Determine reverse direction
    std::string reverse;

    if (direction == "north")      reverse = "south";
    else if (direction == "south") reverse = "north";
    else if (direction == "east")  reverse = "west";
    else if (direction == "west")  reverse = "east";
    else {
        // Unknown direction string; don't add reverse
        return;
    }

    // Add reverse direction
    room2->addExit(reverse, room1);
}



// TODO: Implement run - main game loop
// HINTS:
// - Print welcome message and game title
// - Get player name from input 
// - Create player: player
// - Call initializeWorld()
// - Call createStartingInventory()
// - Display starting room
// - Mark starting room as visited
// - Main loop: 
//   - Print prompt: "> "
//   - Get command (use std::getline)
//   - Convert to lowercase (use std::transform)
//   - Call processCommand()
//   - Check victory condition
//   - Check defeat condition (player dead)
//
void Game::run() {
    std::cout << "========================================" << std::endl;
    std::cout << "      DUNGEON CRAWLER RPG" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Welcome, adventurer!" << std::endl;

    // Get player name
    std::cout << "Enter your name: ";
    std::string name;
    std::getline(std::cin, name);

    if (name.empty()) {
        name = "Hero";
    }

    // Create player
    player = new Player(name);

    // Build world and starting inventory
    initializeWorld();
    createStartingInventory();

    std::cout << "\nType 'help' for a list of commands." << std::endl;
    std::cout << "\nYou find yourself at the entrance of the dungeon..." << std::endl;
    std::cout << std::endl;

    if (current_room != NULL) {
        current_room->display();
        current_room->markVisited();
    }

    // Main game loop
    while (!game_over && player->isAlive() && !victory) {
        std::cout << "\n> ";
        std::string command;
        if (!std::getline(std::cin, command)) {
            // EOF or input error
            break;
        }

        // Convert entire command to lowercase for parsing
        std::transform(command.begin(), command.end(),
                       command.begin(), ::tolower);

        if (command.empty()) {
            continue;
        }

        processCommand(command);

        // defeat condition
        if (!player->isAlive()) {
            game_over = true;
            std::cout << "\nYou have fallen in the dungeon..." << std::endl;
        }

        // victory condition (will be set in combat when Dragon dies)
        if (victory) {
            game_over = true;
            std::cout << "\nYou have defeated the Dragon and cleared the dungeon!" << std::endl;
        }
    }

    std::cout << "\nGame over. Thanks for playing!" << std::endl;
}



// TODO: Implement processCommand
// HINTS:
// - Parse command into verb and object
// - Extract first word as verb
// - Rest of line is object
// - Dispatch to appropriate method based on verb:
//   * "go" or "move" → move(object)
//   * "look" or "l" → look()
//   * "attack" or "fight" → attack()
//   * "pickup" or "get" or "take" → pickupItem(object)
//   * "inventory" or "i" → inventory()
//   * "use" → useItem(object)
//   * "equip" or "e" → equip(object)
//   * "stats" → player->displayStats()
//   * "help" or "h" or "?" → help()
//   * "quit" or "exit" → set game_over to true
//
void Game::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string verb;
    iss >> verb;

    if (verb.empty()) {
        return;
    }

    // Get the rest of the line as the "object"
    std::string object;
    std::getline(iss, object);

    // Trim leading spaces from object
    while (!object.empty() && object[0] == ' ') {
        object.erase(0, 1);
    }

    if (verb == "go" || verb == "move") {
        if (object.empty()) {
            std::cout << "Go where?" << std::endl;
        } else {
            move(object);
        }
    }
    else if (verb == "look" || verb == "l") {
        look();
    }
    else if (verb == "attack" || verb == "fight") {
        attack();
    }
    else if (verb == "pickup" || verb == "get" || verb == "take") {
        if (object.empty()) {
            std::cout << "Pick up what?" << std::endl;
        } else {
            pickupItem(object);
        }
    }
    else if (verb == "inventory" || verb == "i") {
        inventory();
    }
    else if (verb == "use") {
        if (object.empty()) {
            std::cout << "Use what?" << std::endl;
        } else {
            useItem(object);
        }
    }
    else if (verb == "equip" || verb == "e") {
        if (object.empty()) {
            std::cout << "Equip what?" << std::endl;
        } else {
            equip(object);
        }
    }
    else if (verb == "stats") {
        player->displayStats();
    }
    else if (verb == "help" || verb == "h" || verb == "?") {
        help();
    }
    else if (verb == "quit" || verb == "exit") {
        std::cout << "Exiting game..." << std::endl;
        game_over = true;
    }
    else {
        std::cout << "I don't understand that command. Type 'help' for a list of commands." << std::endl;
    }
}



// TODO: Implement move
// HINTS:
// - Check if monster blocks path (current_room->hasMonster())
// - If blocked, print message and return
// - Get exit in specified direction
// - If exit exists:
//   - Update current_room
//   - Display new room
//   - Mark as visited
// - Otherwise print error: "You can't go that way!"
//
void Game::move(const std::string& direction) {
    if (current_room == NULL) {
        std::cout << "You are lost in the void..." << std::endl;
        return;
    }

    // If a monster is still alive in this room, block movement
    if (current_room->hasMonster()) {
        std::cout << "A monster blocks your path! You must defeat it first." << std::endl;
        return;
    }

    Room* next = current_room->getExit(direction);
    if (next == NULL) {
        std::cout << "You can't go that way!" << std::endl;
        return;
    }

    current_room = next;
    std::cout << std::endl;
    current_room->display();
    current_room->markVisited();
}



// TODO: Implement look
// HINTS:
// - Simply display current room
//
void Game::look() {
    if (current_room == NULL) {
        std::cout << "There is nothing to see here." << std::endl;
        return;
    }
    current_room->display();
}



// TODO: Implement attack
// HINTS:
// - Check if monster in room
// - If no monster, print message and return
// - If monster present, call combat()
//
void Game::attack() {
    if (current_room == NULL) {
        std::cout << "There is nothing to attack." << std::endl;
        return;
    }

    if (!current_room->hasMonster()) {
        std::cout << "There is no monster here." << std::endl;
        return;
    }

    Monster* m = current_room->getMonster();
    combat(m);   // combat() will handle the fight (implemented in next task)
}



// TODO: Implement combat
// HINTS:
// - Print "=== COMBAT BEGINS ==="
// - Combat loop: while both player and monster are alive
//   - Prompt for player action: attack/use <item>/flee
//   - If attack:
//     * Calculate player damage
//     * Monster takes damage
//     * If monster dead:
//       - Print victory
//       - Player gains exp and gold
//       - Get loot from monster
//       - Add loot to current room
//       - Check if Dragon 
//       - Clear monster from room
//       - Break from loop
//   - If use:
//     * Extract item name from command
//     * Call player->useItem()
//   - If flee:
//     * Print message and break
//   - Monster turn (if alive):
//     * Print attack message
//     * Calculate monster damage
//     * Player takes damage
// - Print "=== COMBAT ENDS ==="
//
void Game::combat(Monster* monster) {
    if (monster == NULL || player == NULL) {
        std::cout << "There is nothing to fight." << std::endl;
        return;
    }

    std::cout << "\n=== COMBAT BEGINS ===" << std::endl;

    bool fled = false;

    // Combat loop
    while (player->isAlive() && monster->isAlive()) {
        // Display brief status for both
        std::cout << "\nPlayer: ";
        player->displayStatus();
        std::cout << "\nEnemy : ";
        monster->displayStatus();
        std::cout << "\n" << std::endl;

        // Prompt for action
        std::cout << "Choose action (attack / use <item> / flee): ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            // Input error / EOF, treat as flee
            std::cout << "You stumble back from the fight!" << std::endl;
            fled = true;
            break;
        }

        // Convert to lowercase for parsing
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);

        // Parse action
        std::istringstream iss(line);
        std::string verb;
        iss >> verb;

        std::string rest;
        std::getline(iss, rest);
        while (!rest.empty() && rest[0] == ' ') {
            rest.erase(0, 1);
        }

        if (verb == "attack") {
            // Player attacks
            int dmg = player->calculateDamage();
            std::cout << player->getName() << " attacks for " << dmg << " damage!" << std::endl;
            monster->takeDamage(dmg);

            if (!monster->isAlive()) {
                std::cout << "\nYou have defeated the " << monster->getName() << "!" << std::endl;

                // Rewards
                int exp = monster->getExperienceReward();
                int gold = monster->getGoldReward();
                std::cout << "You gain " << exp << " EXP and " << gold << " gold!" << std::endl;

                player->gainExperience(exp);
                player->addGold(gold);

                // Loot drops on the ground (into the room)
                std::vector<Item*> loot = monster->dropLoot();
                if (!loot.empty() && current_room != NULL) {
                    std::cout << "The " << monster->getName() << " dropped:" << std::endl;
                    for (std::size_t i = 0; i < loot.size(); ++i) {
                        std::cout << "  - " << loot[i]->getName() << std::endl;
                        current_room->addItem(loot[i]);  // Room now owns these
                    }
                }

                // Check for boss victory (Dragon)
                if (monster->getName() == "Dragon") {
                    std::cout << "\nYou have slain the Dragon, ruler of this dungeon!" << std::endl;
                    victory = true;
                }

                // Remove monster from the room (and delete it)
                if (current_room != NULL) {
                    current_room->clearMonster();
                }

                break;  // Exit combat loop
            }

        } else if (verb == "use") {
            if (rest.empty()) {
                std::cout << "Use what?" << std::endl;
            } else {
                player->useItem(rest);
            }

        } else if (verb == "flee") {
            std::cout << "You flee from combat!" << std::endl;
            fled = true;
            break;

        } else {
            std::cout << "Unknown action. Type 'attack', 'use <item>', or 'flee'." << std::endl;
        }

        // Monster's turn (if still alive and player didn't flee)
        if (!fled && monster->isAlive() && player->isAlive()) {
            std::cout << "\n" << monster->getAttackMessage() << std::endl;
            int enemy_dmg = monster->calculateDamage();
            std::cout << monster->getName() << " deals " << enemy_dmg << " damage!" << std::endl;
            player->takeDamage(enemy_dmg);
        }

        if (!player->isAlive()) {
            std::cout << "\nYou have been slain by the " << monster->getName() << "..." << std::endl;
            break;
        }
    }

    std::cout << "\n=== COMBAT ENDS ===" << std::endl;
}



// TODO: Implement pickupItem
// HINTS:
// - Get item from current room
// - If exists:
//   - Add to player inventory
//   - Remove from room (ownership transfer!)
// - Otherwise print error
//
void Game::pickupItem(const std::string& item_name) {
    if (current_room == NULL) {
        std::cout << "You are nowhere. There is nothing to pick up." << std::endl;
        return;
    }

    if (item_name.empty()) {
        std::cout << "Pick up what?" << std::endl;
        return;
    }

    Item* item = current_room->getItem(item_name);
    if (item == NULL) {
        std::cout << "There is no item named \"" << item_name << "\" here." << std::endl;
        return;
    }

    // Transfer ownership: Room → Player
    player->addItem(item);
    current_room->removeItem(item_name);
}



// TODO: Implement inventory
//
void Game::inventory() {
    if (player == NULL) {
        std::cout << "There is no player." << std::endl;
        return;
    }
    player->displayInventory();
}



// TODO: Implement useItem
// HINTS:
// - Call player->useItem(item_name)
//
void Game::useItem(const std::string& item_name) {
    if (player == NULL) {
        std::cout << "There is no player." << std::endl;
        return;
    }

    if (item_name.empty()) {
        std::cout << "Use what?" << std::endl;
        return;
    }

    player->useItem(item_name);
}



// TODO: Implement equip
// HINTS:
// - Get item from player inventory
// - Check if item exists
// - Check item type:
//   - If "Weapon": call player->equipWeapon()
//   - If "Armor": call player->equipArmor()
//   - Otherwise: print error (can't equip consumables)
//
void Game::equip(const std::string& item_name) {
    if (player == NULL) {
        std::cout << "There is no player." << std::endl;
        return;
    }

    if (item_name.empty()) {
        std::cout << "Equip what?" << std::endl;
        return;
    }

    Item* item = player->getItem(item_name);
    if (item == NULL) {
        std::cout << "You don't have an item named \"" << item_name << "\"." << std::endl;
        return;
    }

    std::string type = item->getType();
    if (type == "Weapon") {
        player->equipWeapon(item->getName());
    }
    else if (type == "Armor") {
        player->equipArmor(item->getName());
    }
    else {
        std::cout << "You can't equip that item." << std::endl;
    }
}



// TODO: Implement help
// HINTS:
// - Print all available commands with descriptions
// - Format nicely with headers
// - Commands:
//   * go <direction> - Move
//   * look - Look around
//   * attack - Attack monster
//   * pickup <item> - Pick up item
//   * inventory - Show inventory
//   * use <item> - Use consumable
//   * equip <item> - Equip weapon/armor
//   * stats - Show character stats
//   * help - Show this help
//   * quit - Exit game
//
void Game::help() {
    std::cout << "========================================" << std::endl;
    std::cout << "              HELP MENU" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  go <direction>      - Move north, south, east, or west" << std::endl;
    std::cout << "  look                - Look around the current room" << std::endl;
    std::cout << "  attack              - Attack the monster in the room" << std::endl;
    std::cout << "  pickup <item>       - Pick up an item from the room" << std::endl;
    std::cout << "  inventory           - Show your inventory" << std::endl;
    std::cout << "  use <item>          - Use a consumable item" << std::endl;
    std::cout << "  equip <item>        - Equip a weapon or armor" << std::endl;
    std::cout << "  stats               - Show your character stats" << std::endl;
    std::cout << "  help                - Show this help menu" << std::endl;
    std::cout << "  quit                - Exit the game" << std::endl;
    std::cout << "========================================" << std::endl;
}

