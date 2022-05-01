#include "Header-files/Armor.h"

Armor::Armor(int type, int defence, string name, int level, int buyValue, int sellValue, int rarity)
        : Item (name, level, buyValue, sellValue, rarity)
{
    this->type = type;
    this->defence = defence;
}

Armor::~Armor()
{

}
Armor* Armor::clone()const
{
    return new Armor(*this);
}

string Armor::toString()
{
    string str = to_string(this->type) + " " + to_string(this->defence);
    return str;
}