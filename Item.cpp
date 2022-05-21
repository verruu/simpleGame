#include "Header-files/Item.h"

Item::Item()
{
    this->name = "NONE";
    this->itemType = -1;
    this->level = 0;
    this->buyValue = 0;
    this->sellValue = 0;
    this->rarity = -1;
}

Item::Item(int itemType, int level, int rarity)
{
    this->name = "RANDOM";
    this->level = rand() % 4 + level;
    this->rarity = rand() % 5;
    this->buyValue = level*(this->rarity+1)*10;
    this->sellValue = this->buyValue / 5;
    this->itemType = itemType;
}

Item::Item(string name,int itemType, int level, int buyValue, int sellValue, int rarity)
{
    this->name = name;
    this->level = level;
    this->buyValue = buyValue;
    this->sellValue = sellValue;
    this->rarity = rarity;
    this->itemType = itemType;
}

Item::~Item()
{

}