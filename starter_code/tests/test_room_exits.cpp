// tests/test_room_exits.cpp
#include <iostream>
#include "Room.h"

int main() {
    Room room1("Room 1", "First room");
    Room room2("Room 2", "Second room");

    // Add exits between rooms
    room1.addExit("north", &room2);
    room2.addExit("south", &room1);

    std::cout << "=== Display Room 1 ===" << std::endl;
    room1.display();

    std::cout << "\n=== Moving north to Room 2 ===" << std::endl;
    Room* next = room1.getExit("north");
    if (next) {
        next->display();
    } else {
        std::cout << "No exit!" << std::endl;
    }

    return 0;
}
