#ifndef PIRATE_H
#define PIRATE_H

#include <memory>
#include "fleat.h"

using namespace std;
class Pirate
{
public:
    Pirate(int pirate_id);
    ~Pirate();

    void setPirateMoney(int pirate_money);
    void setPirateRank(int pirate_rank);

    int getPirateId() const;
    int getPirateMoney() const;
    int getPirateRank() const;
    shared_ptr<Fleat> getPirateFleat() const;

private:
    int pirate_id;
    int pirate_money;
    int pirate_rank;
    shared_ptr<Fleat> pirate_fleat;
};

#endif // PIRATE_H