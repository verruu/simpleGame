#include "Header-files/Enemy.h"

Enemy::Enemy(int level)
{
    this->level = level;
    this->hpMax = rand() % (level * 5) + level;
    this->hp = this->hpMax;
    this->damageMin = this->level *1;
    this->damageMax = this->level *2;
    this->dropChance = rand() % 100 + 1;
    this->defence = rand() % level*3 + 1;
    this->accuracy = rand() % level*3 + 1;

}

Enemy::~Enemy()
{

}

string Enemy::getAsString() const
{
    return "Level: " + to_string(this->level) + "\n" +
    "HP: " + to_string(this->hp) + " / " + to_string(this->hpMax) + "\n" +
    "Damage: " + to_string(this->damageMin) + " - " + to_string(this->damageMax) + "\n" +
    "Defence: " + to_string(this->defence) + "\n" +
    "Accuracy: " + to_string(this->accuracy) + "\n" +
    "Drop chance: " + to_string(this->dropChance) + "\n";
}

string Enemy::getAsStringEvent() const
{
    stringstream ss;
    ss <<
    "Level: " << this->level <<
    " HP: " << this->hp << "/" << this->hpMax <<
    " Damage: " << this->damageMin << " - " << this->damageMax <<
    " Defence: " << this->defence << " Accuracy: " << this->accuracy;

    return ss.str();
}

void Enemy::takeDamage(int damage)
{
    this->hp -= damage;

    if (this->hp <= 0)
    {
        this->hp = 0;
    }
}