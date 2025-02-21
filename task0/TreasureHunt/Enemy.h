#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

enum class EnemyType {
    Zombie,
    Skeleton,
    Goblin,
    Dragon,
    Boss
};

class Enemy : public Character {
private:
    EnemyType type;

public:
    Enemy(std::string name, int health, int strength, EnemyType type);

    void attack(Character& target) override;
    void takeDamage(int damage) override;

    EnemyType getType();
    void setType(EnemyType type);
};

#endif
