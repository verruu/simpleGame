#include "Header-files/Item.h"

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