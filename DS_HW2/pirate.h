#ifndef PIRATE_H
#define PIRATE_H

#include <memory>
#include "fleet.h"

using namespace std;
class Pirate
{
public:
    Pirate(int pirate_id);
    ~Pirate() = default;

    void setPirateMoney(int pirate_money);
    void setPirateRank(int pirate_rank);
    void setPirateFleet(shared_ptr<Fleet> pirate_fleet);

    int getPirateId() const;
    int getPirateMoney() const;
    int getPirateRank() const;
    shared_ptr<Fleet> getPirateFleet() const;

private:
    int pirate_id;
    int pirate_money;
    int pirate_rank;
    shared_ptr<Fleet> pirate_fleet;
};

#endif // PIRATE_H