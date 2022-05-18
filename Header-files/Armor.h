#pragma once

#include "STLINCLUDE.h"

#include "Item.h"

enum armorType {HEAD = 0, CHEST, ARMS, LEGS};
class Armor :
        public Item
{
public:
    Armor();
    Armor(int level, int rarity);
    Armor(int type, int defence,
           string name, int level,
           int buyValue, int sellValue,
           int rarity);
    virtual ~Armor();

//Pure virtual
    virtual Armor* clone()const;

//Functions
    string toString()const;

//Accessors
inline int getDefence() const { return this->defence; }
inline int getType() const { return this->type; }

//Static
    static dArr<string> names;
    static void initNames();

private:
    int type;
    int defence;
};
