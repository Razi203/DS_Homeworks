
#include "fleat.h"
#include "pirate.h"
#include "consts.h"

using namespace std;

Fleat::Fleat(int fleat_id) : fleat_id(fleat_id), rank_modifier(ZERO), pirates_num(ZERO), ships_num(ONE), fleat_father(nullptr) {}

// Setters -----------------------------------------------------

void Fleat::setRankModifier(int rank_modifier)
{
    rank_modifier = rank_modifier;
}

void Fleat::setPiratesNum(int pirates_num)
{
    pirates_num = pirates_num;
}

void Fleat::setShipsNum(int ships_num)
{
    ships_num = ships_num;
}

void Fleat::setFleatFather(shared_ptr<Fleat> fleat_father)
{
    fleat_father = fleat_father;
}

// Getters -----------------------------------------------------

int Fleat::getFleatId() const
{
    return fleat_id;
}

int Fleat::getRankModifier() const
{
    return rank_modifier;
}

int Fleat::getPiratesNum() const
{
    return pirates_num;
}

shared_ptr<Fleat> Fleat::getFleatFather() const
{
    return fleat_father;
}