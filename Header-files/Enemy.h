#pragma once

#include "dArr.h"
#include <stdlib.h>
#include <string>

using namespace std;

class Enemy
{
public:
    Enemy(int level = 0);
    virtual ~Enemy();

    inline bool isAlive() { return this->hp > 0; }
    string getAsString() const;
    void takeDamage(int damage);
    inline int getLevel() const { return this->level; }
    inline int getDamage() const { return rand() % (this->damageMax - this->damageMin) + this->damageMin; }
    inline int getExp() const { return this->level * 100; }
    inline int getGold() const { return (int) rand() % (int) pow(this->level, 2) + 10; }
    inline int getHp() const { return this->hp; }
    inline int getHpMax() const { return this->hpMax; }
    inline int getDefence() const { return this->defence; }
    inline int getAccuracy() const { return this->accuracy; }
    inline int getDamageMin() const { return this->damageMin; }
    inline int getDamageMax() const { return this->damageMax; }

private:
    int level;
    int hp;
    int hpMax;
    int damageMin;
    int damageMax;
    float dropChance;
    int defence;
    int accuracy;


};
