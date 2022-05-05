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
    inline void takeDamage(int damage) { this->hp -= damage; };
    inline int getDamage() const { return rand() % this->damageMax - this->damageMin; }
    inline int getExp() const { return this->level * 100; }

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
