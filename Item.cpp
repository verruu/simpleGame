#include "Header-files/Item.h"

Item::Item()
{
    this->name = "NONE";
    this->level = 0;
    this->buyValue = 0;
    this->sellValue = 0;
    this->rarity = 0;
}

Item::Item(int level, int rarity)
{
    this->name = "RANDOM";
    this->level = rand() % (level + 3) + level;
    this->rarity = rand() % 5;
    this->buyValue = level*this->rarity*10;
    this->sellValue = buyValue / 5;
}

 Item::Item(string name, int level, int buyValue, int sellValue, int rarity)
 {
    this->name = name;
    this->level = level;
    this->buyValue = buyValue;
    this->sellValue = sellValue;
    this->rarity = rarity;
 }

 Item::~Item()
 {

 }