#ifndef FLEET_H
#define FLEET_H

#include <memory>
using namespace std;

class Fleet
{
public:
    Fleet(int fleet_id);
    ~Fleet() = default;

    shared_ptr<Fleet> getHead(shared_ptr<Fleet> &fleet);

    // getters
    int getFleetId() const;
    int getRankModifier() const;
    int getPiratesNum() const;
    int getShipsNum() const;
    bool isAccessable() const;
    shared_ptr<Fleet> getFleetFather() const;

    // setters
    void setRankModifier(int rank_modifier);
    void setPiratesNum(int pirates_num);
    void setShipsNum(int ships_num);
    void setFleetFather(shared_ptr<Fleet> fleet_father);
    void setAccessable(bool accessable);

private:
    int fleet_id;
    int rank_modifier;
    int pirates_num;
    int ships_num;
    bool accessable;
    shared_ptr<Fleet> fleet_father;
};

#endif // FLEET_H