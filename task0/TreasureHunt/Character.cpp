#include "Character.h"

Character::Character(std::string name, int health, int strength)
    : name(name), health(health), strength(strength) {}

void Character::attack(Character& target) {
    target.takeDamage(strength);
}

void Character::takeDamage(int damage) {
    health -= damage;
}

bool Character::isAlive() {
    return health > 0;
}

std::string Character::getName() { return name; }
int Character::getHealth() { return health; }
int Character::getStrength() { return strength; }

void Character::setHealth(int h) { health = h; }
void Character::setStrength(int s) { strength = s; }

Character::~Character() {}
