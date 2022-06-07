#include "Header-files/Character.h"


Character::Character()
{
    this->distanceTravelled = 0;
    this->gold = 0.0;

    this->name = "";
    this->level = 0;
    this->exp = 0;
    this->expNext = 0;

    this->strength = 0;
    this->vitality = 0;
    this->dexterity = 0;
    this->intelligence = 0;

    this->hp = 0;
    this->hpMax = 0;
    this->stamina = 0;
    this->staminaMax = 0;
    this->damageMax = 0;
    this->damageMin = 0;
    this->defence = 0;
    this->accuracy = 0;
    this->luck = 0;

    this->statPoints = 0;
    this->skillPoints = 0;

    this->flasks = 1;
    this->flaskShards = 0;
    this->flaskShardsMax = 10;
}

Character::Character(string name, int distanceTravelled, int gold, int level,
                     int exp, int flasks, int flaskShards, int strength, int vitality, int dexterity,
                     int intelligence, int hp, int stamina, int statPoints,
                     int skillPoints)
{
    this->distanceTravelled = distanceTravelled;
    this->gold = gold;

    this->name = name;
    this->level = level;
    this->exp = exp;
    this->expNext = 0;

    this->strength = strength;
    this->vitality = vitality;
    this->dexterity = dexterity;
    this->intelligence = intelligence;

    this->hp = hp;
    this->hpMax = 0;
    this->stamina = stamina;
    this->staminaMax = 0;
    this->damageMax = 0;
    this->damageMin = 0;
    this->defence = 0;
    this->accuracy = 0;
    this->luck = 0;

    this->statPoints = statPoints;
    this->skillPoints = skillPoints;

    this->flasks = flasks;
    this->flaskShards = flaskShards;
    this->flaskShardsMax = 10;

//    this->inventory.addItem(Weapon(1, rand() % 5));
//    this->inventory.addItem(Weapon(1, rand() % 5));
//    this->inventory.addItem(Weapon(1, rand() % 5));
//    this->inventory.addItem(Armor(1, rand() % 5));
//    this->inventory.addItem(Armor(1, rand() % 5));
//    this->inventory.addItem(Armor(1, rand() % 5));

    this->updateStats();
}

Character::~Character()
{

}

//functions
void Character::initialize(const string name)
{
    this->distanceTravelled = 0;
    this->gold = 50;

    this->name = name;
    this->level = 1;
    this->exp = 0;
    this->expNext = static_cast<int>
                    ((50/3)*((pow(level,3)-
                    6*pow(level,2))+
                    17*level-12)) + 100;

    this->strength = 5;
    this->vitality = 5;
    this->dexterity = 5;
    this->intelligence = 5;

    this->hpMax = (this->vitality * 2) + (this->strength / 2) + this->level*5;
    this->hp = this->hpMax;
    this->staminaMax = this->vitality + (this->strength / 2) + (this->dexterity / 3);
    this->stamina = this->staminaMax;
    this->damageMax = this->strength * 2;
    this->damageMin = this->strength;
    this->defence = this->dexterity + (this->intelligence / 2);
    this->accuracy = (this->dexterity / 2) + (this->intelligence / 2);
    this->luck = this->intelligence;

    this->statPoints = 0;
    this->skillPoints = 0;

}

void Character::printStats() const
{
    cout << "-= Character Sheet =-" << endl;
    cout << "-= Name: " << this->name << " =-" << endl;
    cout << "-= Level: " << this->level << " =-" << endl;
    cout << "-= Exp: " << this->exp << " =-" << endl;
    cout << "-= Exp to next level: " << this->expNext << " =-" << endl;
    cout << "-= Flasks: " << this->flasks << " =-" << endl;
    cout << "-= Flask shards: " << this->flaskShards << "/" << this->flaskShardsMax << " =-" << endl;
    cout << "-= Stat points: " << this->statPoints << " =-" << endl;
    cout << endl;
    cout << "-= Strength: " << this->strength << " =-" << endl;
    cout << "-= Vitality: " << this->vitality<< " =-" << endl;
    cout << "-= Dexterity: " << this->dexterity << " =-" << endl;
    cout << "-= Intelligence: " << this->intelligence << " =-" << endl;
    cout << endl;
    cout << "-= HP: " << this->hp << "/" << this->hpMax << " =-" << endl;
    cout << "-= Stamina: " << this->stamina << "/" << this->staminaMax << " =-" << endl;
    cout << "-= Damage: " << this->damageMin + this->weapon.getDamageMin() << " - " << this->damageMax + this->weapon.getDamageMax() <<" =-" << endl;
    cout << "-= Defence: " << this->defence +
                              this->armor_legs.getDefence() +
                              this->armor_arms.getDefence() +
                              this->armor_chest.getDefence() +
                              this->armor_head.getDefence() << " =-" << endl;
    cout << "-= Accuracy: " << this->accuracy << " =-" << endl;
    cout << "-= Magic find: " << this->luck << " =-" << endl;
    cout << "-= Distance travelled: " << this->distanceTravelled << " =-" << endl;
    cout << endl;
    cout << "-= Gold: " << this->gold << " =-" << endl;
    cout << "-= Weapon: " << this->weapon.getName()
         << ", level: " << this->weapon.getLevel()
         << ", damage: " << this->weapon.getDamageMin()
         << "/" << this->weapon.getDamageMax()
         << " =-" << endl;
    cout << "-= Armor - head: " << this->armor_head.getName()
         << ", level: " << this->armor_head.getLevel()
         << ", defence: " << this->armor_head.getDefence()
         << " =-" << endl;
    cout << "-= Armor - chest: " << this->armor_chest.getName()
         << ", level: " << this->armor_chest.getLevel()
         << ", defence: " << this->armor_chest.getDefence()
         << " =-" << endl;
    cout << "-= Armor - arms: " << this->armor_arms.getName()
         << ", level: " << this->armor_arms.getLevel()
         << ", defence: " << this->armor_arms.getDefence()
         << " =-" << endl;
    cout << "-= Armor - legs: " << this->armor_legs.getName()
         << ", level: " << this->armor_legs.getLevel()
         << ", defence: " << this->armor_legs.getDefence()
         << " =-" << "\n" << endl;
}

void Character::updateStats()
{
    this->expNext = static_cast<int>
                    ((50/3)*((pow(level,3)-
                    6*pow(level,2))+
                    17*level-12)) + 100;

    this->hpMax = (this->vitality * 2) + (this->strength / 2) + this->level*5;
    this->hp = this->hpMax;
    this->staminaMax = this->vitality + (this->strength / 2) + (this->dexterity / 3);
    this->stamina = this->staminaMax;
    this->damageMax = this->strength * 2;
    this->damageMin = this->strength;
    this->defence = this->dexterity + (this->intelligence / 2);
    this->accuracy = (this->dexterity / 2) + (this->intelligence / 2);
    this->luck = this->intelligence;
}

void Character::levelUp()
{
    if (this->exp >= this->expNext)
    {
        this->exp -= this->expNext;
        this->level++;
        this->expNext = static_cast<int>
                        ((50/3)*((pow(level,3)-
                        6*pow(level,2))+
                        17*level-12)) + 100;

        this->statPoints++;
        this->skillPoints++;

        cout << "You are now level " << level << "!" << "\n\n";
        cout << gui::menu_divider();
    }
    else
    {
        cout << "Not enough EXP!" << "\n\n";
        cout << gui::menu_divider();
    }
}

void Character::addToStat(int stat, int value)
{
    if (this->statPoints < value)
    {
        cout << "ERROR! Not enough stat points!" << "\n\n";
    }
    else
    {
        switch (stat)
        {
            case 0: //STRENGTH
                this->strength += value;
                cout << "Strength increased!" << "\n\n";
                break;
            case 1: //VITALITY
                this->vitality += value;
                cout << "Vitality increased!" << "\n\n";
                break;
            case 2: //DEXTERITY
                this->dexterity += value;
                cout << "Dexterity increased!" << "\n\n";
                break;
            case 3: //INTELLIGENCE
                this->intelligence += value;
                cout << "Intelligence increased!" << "\n\n";
                break;
            default:
                cout << "No such stat!" << "\n\n";
                break;
        }
        this->statPoints -= value;
        cout << gui::menu_divider();
    }
}

string Character::getAsString() const
{
    return  name + " " +
            to_string(distanceTravelled) + " " +
            to_string(gold) + " " +
            to_string(level) + " " +
            to_string(exp) + " " +
            to_string(flasks) + " " +
            to_string(flaskShards) + " " +
            to_string(strength) + " " +
            to_string(vitality) + " " +
            to_string(dexterity) + " " +
            to_string(intelligence) + " " +
            to_string(hp) + " " +
            to_string(stamina) + " " +
            to_string(statPoints) + " " +
            to_string(skillPoints) + " " +
            this->weapon.toStringSave() +
            this->armor_head.toStringSave() +
            this->armor_chest.toStringSave() +
            this->armor_arms.toStringSave() +
            this->armor_legs.toStringSave();
}

void Character::eqItem(unsigned index)
{
    if ( index < 0 || index >= this-> inventory.size())
    {
        cout << "No valid item selected!" << "\n\n";
    } else {
        Weapon *w = nullptr;
        w = dynamic_cast<Weapon *>(&this->inventory[index]);

        Armor *a = nullptr;
        a = dynamic_cast<Armor *>(&this->inventory[index]);

        if (w != nullptr)
        {
            if (this->weapon.getRarity() >= 0)
            this->inventory.addItem(this->weapon);
            this->weapon = *w;
            this->inventory.removeItem(index);
        } else if (a != nullptr)
        {
            switch (a->getType())
            {
                case armorType::HEAD:
                    if (this->armor_head.getRarity() >= 0)
                    this->inventory.addItem(this->armor_head);
                    this->armor_head = *a;
                    this->inventory.removeItem(index);
                    break;
                case armorType::CHEST:
                    if (this->armor_chest.getRarity() >= 0)
                    this->inventory.addItem(this->armor_chest);
                    this->armor_chest = *a;
                    this->inventory.removeItem(index);
                    break;
                case armorType::ARMS:
                    if (this->armor_arms.getRarity() >= 0)
                    this->inventory.addItem(this->armor_arms);
                    this->armor_arms = *a;
                    this->inventory.removeItem(index);
                    break;
                case armorType::LEGS:
                    if (this->armor_legs.getRarity() >= 0)
                    this->inventory.addItem(this->armor_legs);
                    this->armor_legs = *a;
                    this->inventory.removeItem(index);
                    break;
                default:
                    cout << "Error, armor type is invalid!" << "\n\n";
                    break;
            }
        } else {
            cout << "Error, item is neither armor nor weapon!" << "\n\n";
        }
    }
}

void Character::removeItem(const int index)
{
    if (index < 0 || index >= this->inventory.size())
        throw runtime_error("Out of bounds remove!");
    else
    {
        this->inventory.removeItem(index);
    }
}

const Item& Character::getItem(const int index)
{
    if (index < 0 || index >= this->inventory.size())
        throw runtime_error("Out of bounds operation!");
    else
    {
        return this->inventory[index];
    }
}

string Character::getInvAsString(bool shop)
{
    string inv;

    for (size_t i = 0; i < this->inventory.size(); ++i)
    {
        if (shop)
            inv += to_string(i) + ": " + this->inventory[i].toString() + ", Sell value: " + to_string(this->inventory[i].getSellValue()) + "\n";
        else
            inv += to_string(i) + ": " + this->inventory[i].toString() + "\n";
    }

    return inv;
}

string Character::getInvAsStringSave()
{
    string inv;

    for (size_t i = 0; i < this->inventory.size(); ++i)
    {
        if (this->inventory[i].getItemType() == itemTypes::WEAPON)
        inv += this->inventory[i].toStringSave();
    }

    inv += "\n";

    for (size_t i = 0; i < this->inventory.size(); ++i)
    {
        if (this->inventory[i].getItemType() == itemTypes::ARMOR)
            inv += this->inventory[i].toStringSave();
    }

    return inv;
}

void Character::takeDamage(const int damage)
{
    this->hp -= damage;
    if (this->hp <= 0)
    {
        this->hp = 0;
    }
}

const string Character::getCharBar() const
{
    stringstream ss;

    ss << this->name <<
    ". Level: " << this->level << "\n" <<
    "Exp: " << this->exp << "/" << this->expNext <<
    gui::progressBar(this->exp, this->expNext, 20, '-', '=') << "\n" <<
    "HP: " << this->hp << "/" << this->hpMax <<
    gui::progressBar(this->hp, this->hpMax, 20, '-', '=') << "\n" <<
    "Stamina: " << this->stamina << "/" << this->staminaMax <<
    " Flasks: " << this->flasks << " (" << this->flaskShards << "/" << this->flaskShardsMax << ")" <<
    " Distance travelled: " << this->distanceTravelled <<
    " Gold: " << this->gold;

    return ss.str();
}