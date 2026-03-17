# ⚔️ Dungeon Crawler RPG
### ECE 312 — Software Design and Implementation I | UT Austin

A fully playable text-based dungeon crawler written in **C++98**, built from scratch across three weeks as part of ECE 312. No frameworks, no smart pointers — just deliberate object-oriented design, manual memory management, and a working game.

---

## 🎮 Gameplay Overview

Navigate a multi-room dungeon, fight monsters, loot gear, level up, and defeat the Dragon boss to win.

```
> go north
You enter the Dark Hallway.
A skeleton stands in your path!

> attack
--- COMBAT ---
You [HP: 95/100] vs Skeleton [HP: 40/40]
The skeleton rattles its bones and slashes with a sword!
You deal 12 damage. Skeleton HP: 28/40
Skeleton deals 6 damage. Your HP: 89/100
...
```

**Commands**

| Command | Description |
|---|---|
| `go <direction>` | Move north / south / east / west |
| `look` | Describe current room |
| `attack` | Fight the monster in the room |
| `pickup <item>` | Pick up an item from the floor |
| `inventory` | Show your inventory |
| `equip <item>` | Equip a weapon or armor |
| `use <item>` | Use a consumable |
| `stats` | Show player stats |
| `help` | List all commands |
| `quit` | Exit the game |

---

## 🏗️ Architecture

```
Character (base)
├── Player          — inventory, equipment, XP/leveling, gold
└── Monster         — loot table, rewards, attack flavor
    ├── Goblin      — weak, common
    ├── Skeleton    — undead warrior
    └── Dragon      — boss, fire damage bonus

Item (base)
├── Weapon          — attack bonus
├── Armor           — defense bonus
└── Consumable      — single-use healing

Room                — exits (std::map), items, monster
Game                — world graph, game loop, combat system, command parser
```

```
starter_code/
├── include/        # Header files
│   ├── Character.h
│   ├── Player.h
│   ├── Monster.h
│   ├── Item.h
│   ├── Room.h
│   └── Game.h
├── src/            # Implementation files
│   ├── Character.cpp
│   ├── Player.cpp
│   ├── Monster.cpp
│   ├── Item.cpp
│   ├── Room.cpp
│   ├── Game.cpp
│   └── main.cpp
├── tests/          # Unit and integration test programs
├── Makefile
└── Documentation/
```

---

## 🔧 Build & Run

**Prerequisites**: `g++`, `make`, `valgrind` (Linux recommended)

```bash
# Build
make

# Run
./bin/rpg_game

# Clean
make clean

# Rebuild from scratch
make clean && make
```

**Compiler flags**: `-std=c++98 -Wall -Wextra -g`

---

## 🧪 Testing

Individual test programs live in `tests/` and can be compiled independently:

```bash
# Example: test the item hierarchy
g++ -Iinclude -o test_item tests/test_item.cpp src/Item.cpp
./test_item

# Example: test monster polymorphism
g++ -Iinclude -o test_poly tests/test_monster_polymorphism.cpp src/Monster.cpp src/Item.cpp src/Character.cpp
./test_poly
```

**Memory check** (should show zero leaks on a full playthrough):
```bash
valgrind --leak-check=full --show-leak-kinds=all ./bin/rpg_game
```

Test coverage:

| Test File | What It Covers |
|---|---|
| `test_character.cpp` | Damage, healing, death |
| `test_item.cpp` | Base item display |
| `test_weapon/armor/consumable.cpp` | Derived item behavior |
| `test_inventory.cpp` | Vector of Item* management |
| `test_player_inventory.cpp` | Case-insensitive add/remove/search |
| `test_player_equipment.cpp` | Equip system, damage calculation |
| `test_player_levelup.cpp` | XP threshold and stat scaling |
| `test_monster_base.cpp` | Loot drop ownership transfer |
| `test_monster_polymorphism.cpp` | Virtual dispatch through Monster* |
| `test_room_basic/exits/contents.cpp` | Room display, map traversal |
| `test_game_basic.cpp` | Game construction/destruction |

---

## 📚 Concepts Demonstrated

**Object-Oriented Design**
- Inheritance hierarchies with up to three levels (`Dragon → Monster → Character`)
- Virtual function dispatch — `calculateDamage()`, `displayStats()`, `getAttackMessage()` resolved at runtime through base-class pointers
- Constructor chaining via initializer lists across all derived classes

**Memory Management**
- All heap allocation done with `new`/`delete` — no smart pointers
- Explicit ownership model: `Player` owns inventory items, `Room` owns its monster and floor items, `Game` owns all rooms
- Destructors walk ownership trees to prevent leaks
- `equipped_weapon`/`equipped_armor` are *non-owning* pointers into inventory — double-free avoided by design

**STL Containers**
- `std::vector<Item*>` for dynamic inventory and loot tables
- `std::map<std::string, Room*>` for the world graph and room exit connections
- Iterator-based traversal for cleanup and search

**Project Organization**
- Header/source separation with `#ifndef` include guards throughout
- Makefile with dependency tracking — only recompiles what changed
- `std::istringstream` for command parsing (verb + object)

---

## 🗺️ Lab Timeline

| Week | Focus | Key Deliverables |
|---|---|---|
| 1 | Foundation | `Character`, `Item`/`Weapon`/`Armor`/`Consumable`, inventory test |
| 2 | Inheritance & Polymorphism | `Player`, `Monster`/`Goblin`/`Skeleton`/`Dragon`, virtual dispatch |
| 3 | Integration | `Room`, `Game`, command loop, combat system, full playthrough |

**Estimated scope**: ~25–30 hours total

---

## 📝 Notes

- Targets **C++98** standard for compatibility with course servers (`mario.ece.utexas.edu`)
- Assignment from **ECE 312, UT Austin**
- Academic integrity: implementation is original work per course policy

---

*Part of my engineering portfolio — see the [portfolio write-up](#) for a deeper breakdown of design decisions and lessons learned.*
