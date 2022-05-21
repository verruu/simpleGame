#pragma once

#include "STLINCLUDE.h"

#include "Inventory.h"
#include "Enemy.h"

class Character
{
public:
    Character();
    Character(string name, int distanceTravelled, int gold, int level,
              int exp, int strength, int vitality, int dexterity,
              int intelligence, int hp, int stamina, int statPoints,
              int skillPoints);
    virtual ~Character();

//functions
void initialize(const string name);
void printStats() const;
string getAsString() const;
string getInvAsString();
void levelUp();
void updateStats();
void addToStat(int stat, int value);
inline void resetHp() { this->hp = this->hpMax; }
void addItem(const Item &item) { this->inventory.addItem(item); }
void eqItem(unsigned index);

//accessors
inline const int& getDistanceTravelled() const { return this->distanceTravelled; }

inline const string& getName() const { return this->name; }
inline const int& getLevel() const { return this->level; }
inline const int& getExp() const { return this->exp; }
inline const int& getGold() const { return this->gold; }
inline const int& getExpNext() const { return this->expNext; }

inline const int& getStrength() const { return this->strength; }
inline const int& getVitality() const { return this->vitality; }
inline const int& getDexterity() const { return this->dexterity; }
inline const int& getIntelligence() const { return this->intelligence; }

inline const int& getHp() const { return this->hp; }
inline const int& getHpMax() const { return this->hpMax; }
inline const bool isAlive() { return this-> hp > 0; }
inline const int& getStamina() const { return this->stamina; }
inline const int& getStaminaMax() const { return this->staminaMax; }
inline const int& getDamageMin() const { return this->damageMin; }
inline const int& getDamageMax() const { return this->damageMax; }
inline const int getWepDamageMin() const { return this->damageMin + this->weapon.getDamageMin(); }
inline const int getWepDamageMax() const { return this->damageMax + this->weapon.getDamageMax(); }
inline const int getDamage() const { return rand() % ((1 + this->damageMax + this->weapon.getDamageMax()) - (this->damageMin + this->weapon.getDamageMin())) +
                                    +this->damageMin + this->weapon.getDamageMin(); }
inline const int& getDefence() const { return this->defence; }
inline const int& getDefenceMax() const { return this->defence +
                                         this->armor_legs.getDefence() +
                                         this->armor_arms.getDefence() +
                                         this->armor_chest.getDefence() +
                                         this->armor_head.getDefence(); }
inline const int& getAccuracy() const { return this->accuracy; }
inline const int& getLuck() const { return this->luck; }
inline const int getInvSize() const { return this->inventory.size(); }

inline const int& getStatPoints() const { return this->statPoints; }
inline const int& getSkillPoints() const { return this->skillPoints; }

//modifiers
inline void setDistanceTravelled(const int& distance) { this->distanceTravelled = distance; }
inline void travel() { this->distanceTravelled++; }
inline void gainExp(const int exp) { this->exp += exp; }
inline void gainGold(const int gold) { this->gold += gold; }
inline void payGold(const int gold) { this->gold -= gold; }
void takeDamage(const int damage);

private:

    int distanceTravelled;

    Inventory inventory;
    Weapon weapon;
    Armor armor_head;
    Armor armor_chest;
    Armor armor_arms;
    Armor armor_legs;
    int gold;

    string name;
    int level;
    int exp;
    int expNext;

    int strength;
    int vitality;
    int dexterity;
    int intelligence;

    int hp;
    int hpMax;
    int stamina;
    int staminaMax;
    int damageMax;
    int damageMin;
    int defence;
    int accuracy;
    int luck;

    int statPoints;
    int skillPoints;

};