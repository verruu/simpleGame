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
    this->type = -1;
    this->defence = 0;
}

Armor::Armor(int level, int rarity):Item(itemTypes::ARMOR, level, rarity)
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
        : Item (name, itemTypes::ARMOR, level, buyValue, sellValue, rarity)
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
                to_string(this->defence) + ".";
    return str;
}

string Armor::toStringSave() const
{
    string str = to_string(this->getItemType()) + " " +
                 this->getName() + " " +
                 to_string(this->getLevel()) + " " +
                 to_string(this->getRarity()) + " " +
                 to_string(this->type) + " " +
                 to_string(this->defence) + " " +
                 to_string(this->getSellValue()) + " " +
                 to_string(this->getBuyValue()) + " ";
    return str;
}