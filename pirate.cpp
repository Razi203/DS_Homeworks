
#include "pirate.h"
#include "consts.h"

Pirate::Pirate(int pirate_id) : pirate_id(pirate_id), pirate_money(ZERO), pirate_rank(ZERO), pirate_fleat(nullptr) {}

// Setters -----------------------------------------------------
void Pirate::setPirateMoney(int pirate_money)
{
    pirate_money = pirate_money;
}

void Pirate::setPirateRank(int pirate_rank)
{
    pirate_rank = pirate_rank;
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

shared_ptr<Fleat> Pirate::getPirateFleat() const
{
    return pirate_fleat;
}
