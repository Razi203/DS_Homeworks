#ifndef PIRATES_H
#define PIRATES_H

#include "wet1util.h"
#include "consts.h"

#include <memory>

using namespace std;

class Ship;
class Pirate;
class PirateCompare;
class MoneyCompare;
class Pirate
{

public:
    Pirate(int id, int value) : pirateId(id), treasure(value) {}
    ~Pirate() = default;

    void print(ostream &os) const;
    friend ostream &operator<<(ostream &os, const Pirate &pirate);

    // Setters
    void setPirateId(int id);
    void setTreasure(int value);
    void setPrev(shared_ptr<Pirate> p);
    void setNext(shared_ptr<Pirate> n);
    void setShip(shared_ptr<Ship> s);

    // Getters
    int getPirateId() const;
    int getTreasure() const;
    shared_ptr<Pirate> getPrev() const;
    shared_ptr<Pirate> getNext() const;
    shared_ptr<Ship> getShip() const;

private:
    int pirateId;
    int treasure;
    weak_ptr<Pirate> prev, next;
    weak_ptr<Ship> ship;
};

class PirateCompare // true if b > a
{
public:
    bool operator()(const shared_ptr<Pirate> a, const shared_ptr<Pirate> b) const
    {
        return a->getPirateId() < b->getPirateId();
    }
};

class MoneyCompare // true if b > a
{
public:
    bool operator()(const shared_ptr<Pirate> a, const shared_ptr<Pirate> b) const
    {
        if (a->getTreasure() < b->getTreasure())
            return true;
        else if (a->getTreasure() > b->getTreasure())
            return false;
        else if (a->getPirateId() < b->getPirateId())
            return true;
        else
            return false;
    }
};

#endif