#include "Header-files/Weapon.h"

Weapon::Weapon(int damageMin, int damageMax, string name, int level, int buyValue, int sellValue, int rarity)
: Item (name, level, buyValue, sellValue, rarity)
{
    this->damageMin = damageMin;
    this->damageMax = damageMax;
}

Weapon::~Weapon()
{

}
Weapon* Weapon::clone()const
{
    return new Weapon(*this);
}

string Weapon::toString()
{
    string str = to_string(this->damageMin) + " " + to_string(this->damageMax);
    return str;
}