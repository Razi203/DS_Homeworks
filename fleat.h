#ifndef FLEAT_H
#define FLEAT_H

#include <memory>
using namespace std;

class Fleat
{
public:
    Fleat(int fleat_id);
    ~Fleat();

    int getFleatId() const;
    int getRankModifier() const;
    int getPiratesNum() const;
    int getShipsNum() const;
    shared_ptr<Fleat> getFleatFather() const;

    void setRankModifier(int rank_modifier);
    void setPiratesNum(int pirates_num);
    void setShipsNum(int ships_num);
    void setFleatFather(shared_ptr<Fleat> fleat_father);

private:
    int fleat_id;
    int rank_modifier;
    int pirates_num;
    int ships_num;
    shared_ptr<Fleat> fleat_father;
};

#endif // FLEAT_H