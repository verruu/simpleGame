#pragma once

#include "STLINCLUDE.h"

#include "Item.h"

class Weapon :
        public Item
{
public:
    Weapon();
    Weapon(int level, int rarity);
    Weapon(int damageMin, int damageMax,
           string name, int level,
           int buyValue, int sellValue,
           int rarity);
    virtual ~Weapon();

//Pure virtual
    virtual Weapon* clone()const;

//Functions
    string toString()const;

//Accessors
inline int getDamageMin() const { return this-> damageMin; }
inline int getDamageMax() const { return this-> damageMax; }

//Modifiers

//Static
    static dArr<string> names;
    static void initNames();

private:
    int damageMin;
    int damageMax;
};
