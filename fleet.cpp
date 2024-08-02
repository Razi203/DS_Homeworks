
#include "fleet.h"
#include "pirate.h"
#include "consts.h"

using namespace std;

Fleet::Fleet(int fleet_id) : fleet_id(fleet_id), rank_modifier(ZERO), pirates_num(ZERO), ships_num(ONE), fleet_father(nullptr), accessable(true) {}

// Setters -----------------------------------------------------

void Fleet::setRankModifier(int rank_modifier)
{
    rank_modifier = rank_modifier;
}

void Fleet::setPiratesNum(int pirates_num)
{
    pirates_num = pirates_num;
}

void Fleet::setShipsNum(int ships_num)
{
    ships_num = ships_num;
}

void Fleet::setFleetFather(shared_ptr<Fleet> fleet_father)
{
    fleet_father = fleet_father;
}

// Getters -----------------------------------------------------

int Fleet::getFleetId() const
{
    return fleet_id;
}

int Fleet::getRankModifier() const
{
    return rank_modifier;
}

int Fleet::getPiratesNum() const
{
    return pirates_num;
}

shared_ptr<Fleet> Fleet::getFleetFather() const
{
    return fleet_father;
}

bool Fleet::isAccessable() const
{
    return accessable;
}