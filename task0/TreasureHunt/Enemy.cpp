#include "Enemy.h"

Enemy::Enemy(std::string name, int health, int strength, EnemyType type)
    : Character(name, health, strength), type(type) {}

void Enemy::attack(Character& target) {
    int damage = strength;

    switch (type) {
    case EnemyType::Zombie:
        damage += 2;
        break;
    case EnemyType::Skeleton:
        damage -= 1;
        break;
    case EnemyType::Goblin:
        damage += 1;
        break;
    case EnemyType::Dragon:
        damage *= 2;
        break;
    case EnemyType::Boss:
        damage += 5;
        break;
    default:
        break;
    }

    target.takeDamage(damage);
}

void Enemy::takeDamage(int damage) {
    switch (type) {
    case EnemyType::Zombie:
        damage -= 1;
        break;
    case EnemyType::Skeleton:
        damage += 1;
        break;
    case EnemyType::Goblin:
        damage -= 2;
        break;
    case EnemyType::Dragon:
        damage /= 2;
        break;
    case EnemyType::Boss:
        damage -= 3;
        break;
    default:
        break;
    }

    if (damage < 0) {
        damage = 0;
    }

    health -= damage;
}

EnemyType Enemy::getType() { return type; }

void Enemy::setType(EnemyType t) { type = t; }
