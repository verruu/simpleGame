#include "Header-files/Weapon.h"

dArr<string> Weapon::names;

void Weapon::initNames()
{
    Weapon::names.push("Exacto-knife");
    Weapon::names.push("Spiked-sword");
    Weapon::names.push("Katana");
    Weapon::names.push("Zweihander");
    Weapon::names.push("Morning-star");
    Weapon::names.push("Hand-axe");
}

Weapon::Weapon():Item()
{
    this->damageMax = 0;
    this->damageMin = 0;

}

Weapon::Weapon(int level, int rarity):Item(itemTypes::WEAPON, level, rarity)
{
    this->damageMax = (rand() % level + 1) * rarity + level;
    this->setName(Weapon::names[rand() % Weapon::names.size()]);
    if (rarity == 3)
        this->damageMax += level * rarity;
    else if (rarity == 4)
        this->damageMax += 2 * level * rarity;
    this->damageMin = damageMax / 2;
}

Weapon::Weapon(int damageMin, int damageMax, string name, int level, int buyValue, int sellValue, int rarity)
: Item (name, itemTypes::WEAPON, level, buyValue, sellValue, rarity)
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

string Weapon::toString()const
{
    string str = this->getName() + ". Level: " +
            to_string(this->getLevel()) + ", rarity: " +
            to_string(this->getRarity()) + ", damage: " +
            to_string(this->damageMin) + "/" +
            to_string(this->damageMax) + ".";
    return str;
}

string Weapon::toStringSave() const
{
    string str = to_string(this->getItemType()) + " " +
                 this->getName() + " " +
                 to_string(this->getLevel()) + " " +
                 to_string(this->getRarity()) + " " +
                 to_string(this->damageMin) + " " +
                 to_string(this->damageMax) + " " +
                 to_string(this->getSellValue()) + " " +
                 to_string(this->getBuyValue()) + " ";
    return str;
}