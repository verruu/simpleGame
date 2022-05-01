#pragma once

#include "Item.h"

class Weapon :
        public Item
{
public:
    Weapon(int damageMin = 0, int damageMax = 0,
           string name = "NONE", int level = 0,
           int buyValue = 0, int sellValue = 0,
           int rarity = 0);
    virtual ~Weapon();

//Pure virtual
    virtual Weapon* clone()const;

//Functions
    string toString();

private:
    int damageMin;
    int damageMax;
};
