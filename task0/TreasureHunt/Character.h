#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
protected:
    std::string name;
    int health;
    int strength;

public:
    Character(std::string name, int health, int strength);

    virtual void attack(Character& target);
    virtual void takeDamage(int damage);
    virtual bool isAlive();

    std::string getName();
    int getHealth();
    int getStrength() ;

    void setHealth(int health);
    void setStrength(int strength);

    virtual ~Character();
};

#endif
