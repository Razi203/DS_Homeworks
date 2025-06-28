#include "ship.h"
#include <iostream>

using namespace std;

void Ship::print(ostream &os) const
{
    // os << shipId;
    os << "Ship ID: " << shipId << ", Cannon Amount: " << cannon_count;
}

ostream &operator<<(ostream &os, const Ship &ship)
{
    ship.print(os);
    return os;
}

// Setters
void Ship::setShipId(int id)
{
    shipId = id;
}

void Ship::setCannonCount(int count)
{
    cannon_count = count;
}

void Ship::setPirateCount(int count)
{
    pirate_count = count;
}

void Ship::setFirstPirate(shared_ptr<Pirate> pirate)
{
    first_pirate = pirate;
}
void Ship::setLastPirate(shared_ptr<Pirate> pirate)
{
    last_pirate = pirate;
}

void Ship::setTreasureModifier(int change)
{
    treasure_modifier = change;
}

// Getters
int Ship::getShipId() const
{
    return shipId;
}

int Ship::getCannonCount() const
{
    return cannon_count;
}

int Ship::getPirateCount() const
{
    return pirate_count;
}

int Ship::getTreasureModifier() const
{
    return treasure_modifier;
}
AVLTree<Pirate, MoneyCompare> &Ship::getMoneyPirates()
{
    return money_pirates;
}
shared_ptr<Pirate> Ship::getFirstPirate() const
{
    return first_pirate.lock();
}
shared_ptr<Pirate> Ship::getLastPirate() const
{
    return last_pirate.lock();
}
