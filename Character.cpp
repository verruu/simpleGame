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
}

Character::Character(string name, int distanceTravelled, int gold, int level,
                     int exp, int strength, int vitality, int dexterity,
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

    this->inventory.addItem(Weapon(1, rand() % 5));
    this->inventory.addItem(Weapon(1, rand() % 5));
    this->inventory.addItem(Armor(1, rand() % 5));

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
    cout << "-= Stat points: " << this->statPoints << " =-" << endl;
    cout << endl;
    cout << "-= Strength: " << this->strength << " =-" << endl;
    cout << "-= Vitality: " << this->vitality<< " =-" << endl;
    cout << "-= Dexterity: " << this->dexterity << " =-" << endl;
    cout << "-= Intelligence: " << this->intelligence << " =-" << endl;
    cout << endl;
    cout << "-= HP: " << this->hp << "/" << this->hpMax << " =-" << endl;
    cout << "-= Stamina: " << this->stamina << "/" << this->staminaMax << " =-" << endl;
    cout << "-= Damage: " << this->damageMin << " - " << this->damageMax <<" =-" << endl;
    cout << "-= Defence: " << this->defence << " =-" << endl;
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
    }
    else
    {
        cout << "Not enough EXP!" << "\n\n";
    }
}

void Character::addToStat(int stat, int value)
{
    if (this->statPoints < value)
    {
        cout << "ERROR! Not enough stat points!" << "\n";
    }
    else
    {
        switch (stat)
        {
            case 0: //STRENGTH
                this->strength += value;
                cout << "Strength increased!" << "\n";
                break;
            case 1: //VITALITY
                this->vitality += value;
                cout << "Vitality increased!" << "\n";
                break;
            case 2: //DEXTERITY
                this->dexterity += value;
                cout << "Dexterity increased!" << "\n";
                break;
            case 3: //INTELLIGENCE
                this->intelligence += value;
                cout << "Intelligence increased!" << "\n";
                break;
            default:
                cout << "No such stat!" << "\n";
                break;
        }
        this->statPoints -= value;
    }
}

string Character::getAsString() const
{
    return  name + " " +
            to_string(distanceTravelled) + " " +
            to_string(gold) + " " +
            to_string(level) + " " +
            to_string(exp) + " " +
            to_string(strength) + " " +
            to_string(vitality) + " " +
            to_string(dexterity) + " " +
            to_string(intelligence) + " " +
            to_string(hp) + " " +
            to_string(stamina) + " " +
            to_string(statPoints) + " " +
            to_string(skillPoints);
}

string Character::getInvAsString()
{
    string inv;

    for (size_t i = 0; i < this->inventory.size(); ++i)
    {
        inv += to_string(i) + ": " + this->inventory[i].toString() + "\n";
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