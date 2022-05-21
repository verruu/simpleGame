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

    switch (this->type)
    {
        case armorType::HEAD:
            this->typeStr = "Head";
            break;
        case armorType::CHEST:
            this->typeStr = "Chest";
            break;
        case armorType::ARMS:
            this->typeStr = "Arms";
            break;
        case armorType::LEGS:
            this->typeStr = "Legs";
            break;
        default:
            this->typeStr = "ERROR!";
            break;
    }

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
    string str = this->getName() + ". Type: " +
                this->typeStr + ", level: " +
                to_string(this->getLevel()) + ", rarity: " +
                to_string(this->getRarity()) + ", defence: " +
                to_string(this->defence) + ", sell value: " +
                to_string(this->getSellValue()) + ".";
    return str;
}