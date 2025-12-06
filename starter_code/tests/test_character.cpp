#include "Character.h"

int main() {
    Character hero("Hero", 100, 10, 5);
    hero.displayStats();
    hero.takeDamage(20);
    hero.heal(10);
    return 0;
}