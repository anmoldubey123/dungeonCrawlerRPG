// tests/test_player_levelup.cpp
#include <iostream>
#include "Player.h"
#include "Item.h"

int main() {
    Player hero("Dana");

    std::cout << "=== Initial Stats ===" << std::endl;
    hero.displayStats();

    std::cout << "\n=== Gaining 100 EXP ===" << std::endl;
    hero.gainExperience(100);  // Should trigger level up

    std::cout << "\n=== Stats After Level Up ===" << std::endl;
    hero.displayStats();

    return 0;
}
