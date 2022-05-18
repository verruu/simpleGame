#pragma once

#include "STLINCLUDE.h"

using namespace std;

class Item {
public:
    Item();
    Item(int level, int rarity);
    Item(string name,
         int level,
         int buyValue,
         int sellValue,
         int rarity);
    virtual ~Item();

    inline string debugPrint() const {return this-> name;}
    virtual Item* clone()const = 0;
    virtual string toString()const = 0;

//Accessors
    inline const string& getName() const {return this-> name;}
    inline const int& getLevel() const {return this-> level;}
    inline const int& getBuyValue() const {return this-> buyValue;}
    inline const int& getSellValue() const {return this-> sellValue;}
    inline const int& getRarity() const {return this-> rarity;}

//Modifiers
    inline void setName(string name) { this->name = name; }

//Static

private:
    string name;
    int level;
    int sellValue;
    int buyValue;
    int rarity;
};

enum rarity
{
    common = 0, uncommon, rare, epic, legendary
};