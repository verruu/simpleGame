#include "Header-files/Armor.h"

dArr<string> Armor::names;

void Armor::initNames()
{
    Armor::names.push("Gloves");
    Armor::names.push("Boots");
    Armor::names.push("Armor");
    Armor::names.push("Helmet");
    Armor::names.push("Shield");
}

Armor::Armor():Item()
{
    this->defence = 0;
}

Armor::Armor(int level, int rarity):Item(level, rarity)
{
    this->defence = (rand() % level + 1) * rarity + level;
    this->type = rand() % 4;
    this->setName(Armor::names[rand() % Armor::names.size()]);
    if (rarity == 3)
        this->defence += level * rarity;
    else if (rarity == 4)
        this->defence += 2 * level * rarity;
}

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

string Armor::toString()const
{
    string str = this->getName() + " " +
                to_string(this->type) + " " +
                to_string(this->getLevel()) + " " +
                to_string(this->getRarity()) + " " +
                to_string(this->defence) + " " +
                to_string(this->getSellValue());;
    return str;
}