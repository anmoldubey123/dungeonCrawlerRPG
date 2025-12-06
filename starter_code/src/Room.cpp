#include "Room.h"
#include <iostream>
#include <algorithm>

// TODO: Implement Room constructor
Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description), visited(false), monster(NULL) {
}


// TODO: Implement Room destructor
Room::~Room() {
    // Delete monster if present
    if (monster != NULL) {
        delete monster;
        monster = NULL;
    }

    // Delete all items on the ground
    for (std::size_t i = 0; i < items.size(); i++) {
        delete items[i];
    }
    items.clear();

    // DO NOT delete exits — Game owns the rooms!!
}



// TODO: Implement display
// HINTS:
// - Print formatted room information with decorative borders
// - Format:
//   ========================================
//   Room Name
//   ========================================
//   Description text
//   
//   [If monster] A MonsterName blocks your path!
//   
//   [If items] Items here:
//     - item1
//     - item2
//   
//   Exits: north, south, east
//   ========================================
//
void Room::display() const {
    std::cout << "========================================" << std::endl;
    std::cout << name << std::endl;
    std::cout << "========================================" << std::endl;

    std::cout << description << std::endl << std::endl;

    // Monster present?
    if (monster != NULL && monster->isAlive()) {
        std::cout << "A " << monster->getName() << " blocks your path!" << std::endl;
        std::cout << std::endl;
    }

    // Items present?
    if (!items.empty()) {
        std::cout << "Items here:" << std::endl;
        for (std::size_t i = 0; i < items.size(); i++) {
            std::cout << "  - " << items[i]->getName() << std::endl;
        }
        std::cout << std::endl;
    }

    // Exits
    displayExits();

    std::cout << "========================================" << std::endl;
}



// TODO: Implement displayExits
// HINTS:
// - Print "Exits: "
// - Iterate through exits map using iterator
// - Print each direction (the key) separated by commas
// - Example output: "Exits: north, south, east"
//
void Room::displayExits() const {
    std::cout << "Exits: ";

    if (exits.empty()) {
        std::cout << "none";
    } else {
        bool first = true;
        for (std::map<std::string, Room*>::const_iterator it = exits.begin();
             it != exits.end(); ++it)
        {
            if (!first) std::cout << ", ";
            std::cout << it->first;
            first = false;
        }
    }

    std::cout << std::endl;
}



// TODO: Implement addExit
// HINTS:
// - Check if room pointer is not NULL
// - Add to exits map: exits[direction] = room
//
void Room::addExit(const std::string& direction, Room* room) {
    if (room == NULL) {
        std::cout << "Cannot add exit to NULL room!" << std::endl;
        return;
    }
    exits[direction] = room;
}



// TODO: Implement getExit
// HINTS:
// - Look up direction in exits map
// - Use exits.find(direction)
// - If not found, return NULL
//
Room* Room::getExit(const std::string& direction) const {
    std::map<std::string, Room*>::const_iterator it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    return NULL;
}



// TODO: Implement hasExit
// HINTS:
// - Check if direction exists in exits map
bool Room::hasExit(const std::string& direction) const {
    return exits.find(direction) != exits.end();
}



// TODO: Implement clearMonster
// HINTS:
// - If monster exists, delete it
// - Set monster pointer to NULL
//
void Room::clearMonster() {
    if (monster != NULL) {
        delete monster;
        monster = NULL;
    }
}



// TODO: Implement addItem
// HINTS:
// - Check if item pointer is not NULL
// - Add to items vector using push_back()
//
void Room::addItem(Item* item) {
    if (item == NULL) {
        std::cout << "Cannot add NULL item to room." << std::endl;
        return;
    }
    items.push_back(item);
}



// TODO: Implement removeItem
// HINTS:
// - Search items vector for item by name (case-insensitive)
// - If found: erase from vector (DON'T delete - ownership transferred)
//
void Room::removeItem(const std::string& item_name) {
    if (items.empty()) {
        return;
    }

    // Lowercase target for case-insensitive comparison
    std::string lower_target = item_name;
    std::transform(lower_target.begin(), lower_target.end(),
                   lower_target.begin(), ::tolower);

    for (std::size_t i = 0; i < items.size(); ++i) {
        std::string lower_item = items[i]->getName();
        std::transform(lower_item.begin(), lower_item.end(),
                       lower_item.begin(), ::tolower);

        if (lower_item == lower_target) {
            // DO NOT delete here — ownership has been transferred
            items.erase(items.begin() + i);
            return;
        }
    }
}



// TODO: Implement displayItems
// HINTS:
// - Print each item's name in a list
// - Format: "  - ItemName"
//
void Room::displayItems() const {
    for (std::size_t i = 0; i < items.size(); ++i) {
        std::cout << "  - " << items[i]->getName() << std::endl;
    }
}



// TODO: Implement getItem
// HINTS:
// - Search items vector for item by name (case-insensitive)
// - If found, return pointer to item
// - If not found, return NULL
//
Item* Room::getItem(const std::string& item_name) {
    std::string lower_target = item_name;
    std::transform(lower_target.begin(), lower_target.end(),
                   lower_target.begin(), ::tolower);

    for (std::size_t i = 0; i < items.size(); ++i) {
        std::string lower_item = items[i]->getName();
        std::transform(lower_item.begin(), lower_item.end(),
                       lower_item.begin(), ::tolower);

        if (lower_item == lower_target) {
            return items[i];
        }
    }

    return NULL;
}

