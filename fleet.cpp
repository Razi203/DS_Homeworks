
#include "fleet.h"
#include "pirate.h"
#include "consts.h"

using namespace std;

Fleet::Fleet(int fleet_id) : fleet_id(fleet_id), rank_modifier(ZERO),
                             pirates_num(ZERO), ships_num(ONE), fleet_father(nullptr), accessable(true) {}

shared_ptr<Fleet> Fleet::getHead(shared_ptr<Fleet> &fleet)
{
    if (fleet->getFleetFather() == nullptr)
    {
        return fleet;
    }
    auto head = fleet->getFleetFather();
    int rank_sum = fleet->getRankModifier();
    while (head->getFleetFather() != nullptr)
    {
        rank_sum += head->getRankModifier();
        head = head->getFleetFather();
    }

    while (fleet->getFleetFather() != head)
    {
        auto temp = fleet->getFleetFather();
        fleet->setFleetFather(head);
        rank_sum -= fleet->getRankModifier();
        fleet->setRankModifier(fleet->getRankModifier() + rank_sum);
        fleet = temp;
    }

    return head;
}

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

void Fleet::setAccessable(bool accessable)
{
    accessable = accessable;
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

int Fleet::getShipsNum() const
{
    return ships_num;
}
