
#include "pirate.h"
#include "consts.h"

Pirate::Pirate(int pirate_id) : pirate_id(pirate_id), pirate_money(ZERO), pirate_rank(ZERO), pirate_fleet(nullptr) {}

// Setters -----------------------------------------------------
void Pirate::setPirateMoney(int pirate_money)
{
    this->pirate_money = pirate_money;
}

void Pirate::setPirateRank(int pirate_rank)
{
    this->pirate_rank = pirate_rank;
}

void Pirate::setPirateFleet(shared_ptr<Fleet> pirate_fleet)
{
    this->pirate_fleet = pirate_fleet;
}

// Getters -----------------------------------------------------
int Pirate::getPirateId() const
{
    return pirate_id;
}

int Pirate::getPirateMoney() const
{
    return pirate_money;
}

int Pirate::getPirateRank() const
{
    return pirate_rank;
}

shared_ptr<Fleet> Pirate::getPirateFleet() const
{
    return pirate_fleet;
}
