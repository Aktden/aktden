#include "Player.h"

Player::Player(std::string name, int health, int strength, int level)
    : Character(name, health, strength), level(level) {}

void Player::attack(Character& target) {
    int adjustedStrength = strength * level;
    target.takeDamage(adjustedStrength);
}

int Player::getLevel() const { return level; }

void Player::setLevel(int lvl) { level = lvl; }
