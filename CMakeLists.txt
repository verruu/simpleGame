cmake_minimum_required(VERSION 3.22)
project(first_game)

set(CMAKE_CXX_STANDARD 23)

add_executable(first_game main.cpp Game.cpp Header-files/Game.h Header-files/Functions.h Character.cpp Header-files/Character.h Item.cpp Header-files/Item.h Inventory.cpp Header-files/Inventory.h Weapon.cpp Header-files/Weapon.h Armor.cpp Header-files/Armor.h Enemy.cpp Header-files/Enemy.h Event.cpp Header-files/Event.h Puzzle.cpp Header-files/Puzzle.h)
