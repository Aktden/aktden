#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
private:
    int level;

public:
    Player(std::string name, int health, int strength, int level);

    void attack(Character& target) override;

    int getLevel() const;
    void setLevel(int level);
};

#endif
