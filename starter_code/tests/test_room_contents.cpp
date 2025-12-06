// tests/test_room_contents.cpp
#include <iostream>
#include "Room.h"
#include "Monster.h"
#include "Item.h"

int main() {
    Room room("Armory", "Weapons everywhere");

    room.addItem(new Weapon("Sword", "Sharp", 5));
    room.setMonster(new Goblin());

    std::cout << "=== Room Display ===" << std::endl;
    room.display();

    if (room.hasMonster()) {
        std::cout << "Monster present!" << std::endl;
    } else {
        std::cout << "No monster present." << std::endl;
    }

    // Room destructor will clean up:
    // - the Goblin (monster)
    // - the Sword (item)
    return 0;
}
