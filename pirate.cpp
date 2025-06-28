#include "pirate.h"
#include "ship.h"

#include <iostream>

using namespace std;

void Pirate::print(ostream &os) const
{
    os << "Pirate ID: " << pirateId << ", Treasure: " << treasure + getShip()->getTreasureModifier();
}

ostream &operator<<(ostream &os, const Pirate &pirate)
{
    pirate.print(os);
    return os;
}

// Setters --------------------------------------------
void Pirate::setPirateId(int id)
{
    pirateId = id;
}

void Pirate::setTreasure(int value)
{
    treasure = value;
}

void Pirate::setPrev(shared_ptr<Pirate> p)
{
    prev = p;
}
void Pirate::setNext(shared_ptr<Pirate> n)
{
    next = n;
}

void Pirate::setShip(shared_ptr<Ship> s)
{
    ship = s;
}

// Getters --------------------------------------------

int Pirate::getPirateId() const
{
    return pirateId;
}

int Pirate::getTreasure() const
{
    return treasure;
}

shared_ptr<Pirate> Pirate::getPrev() const
{
    return prev.lock();
}
shared_ptr<Pirate> Pirate::getNext() const
{
    return next.lock();
}
shared_ptr<Ship> Pirate::getShip() const
{
    return ship.lock();
}