#include "pirates24b1.h"
#include <iostream>

Ocean::Ocean() : ships_tree(ShipCompare()), pirates_tree(PirateCompare()) {}

Ocean::~Ocean() = default;

StatusType Ocean::add_ship(int shipId, int cannons)
{
    if (shipId <= ZERO || cannons < ZERO)
    {
        return StatusType::INVALID_INPUT;
    }

    auto location = findShipLocation(shipId);
    if (location != nullptr && location->inner_node->getShipId() == shipId)
    {
        return StatusType::FAILURE;
    }

    shared_ptr<Ship> new_ship;
    shared_ptr<AVLTreeNode<Ship>> new_ship_node;
    try
    {
        new_ship = make_shared<Ship>(shipId, cannons);
        ships_tree.insert(new_ship);
    }
    catch (bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Ocean::remove_ship(int shipId)
{
    if (shipId <= ZERO)
    {
        return StatusType::INVALID_INPUT;
    }
    auto ship = findShip(shipId);

    if (ship == nullptr || ship->getPirateCount() > ZERO)
    {
        return StatusType::FAILURE;
    }
    ships_tree.remove(ship);
    return StatusType::SUCCESS;
}

StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure)
{
    if (pirateId <= ZERO || shipId <= ZERO)
    {
        return StatusType::INVALID_INPUT;
    }

    auto location = findPirateLocation(pirateId);
    if (location != nullptr && location->inner_node->getPirateId() == pirateId)
    {
        return StatusType::FAILURE;
    }
    auto ship = findShip(shipId);
    if (ship == nullptr || ship->getShipId() != shipId)
    {
        return StatusType::FAILURE;
    }
    shared_ptr<Pirate> new_pirate;
    shared_ptr<AVLTreeNode<Pirate>> new_pirate_node;
    try
    {
        new_pirate = make_shared<Pirate>(pirateId, treasure);
        int dest_trasure_modifier = ship->getTreasureModifier();
        new_pirate->setShip(ship);
        new_pirate->setTreasure(treasure - dest_trasure_modifier);

        pirates_tree.insert(new_pirate);
        if (ship->getPirateCount() == ZERO)
        {
            ship->setFirstPirate(new_pirate);
        }
        else
        {
            ship->getLastPirate()->setNext(new_pirate);
            new_pirate->setPrev(ship->getLastPirate());
        }
        ship->setPirateCount(ship->getPirateCount() + ONE);
        ship->getMoneyPirates().insert(new_pirate);
        ship->setLastPirate(new_pirate);
    }
    catch (bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Ocean::remove_pirate(int pirateId)
{
    if (pirateId <= ZERO)
    {
        return StatusType::INVALID_INPUT;
    }
    auto pirate = findPirate(pirateId);
    if (pirate == nullptr)
    {
        return StatusType::FAILURE;
    }
    auto ship = pirate->getShip();
    pirates_tree.remove(pirate);
    ship->getMoneyPirates().remove(pirate);

    if (ship->getPirateCount() == ONE)
    {
        ship->setFirstPirate(nullptr);
        ship->setLastPirate(nullptr);
    }
    else if (ship->getFirstPirate()->getPirateId() == pirateId)
    {
        ship->setFirstPirate(pirate->getNext());
        pirate->getNext()->setPrev(nullptr);
    }
    else if (ship->getLastPirate()->getPirateId() == pirateId)
    {
        ship->setLastPirate(pirate->getPrev());
        pirate->getPrev()->setNext(nullptr);
    }
    else
    {
        pirate->getPrev()->setNext(pirate->getNext());
        pirate->getNext()->setPrev(pirate->getPrev());
    }
    pirate->setShip(nullptr);
    pirate->setNext(nullptr);
    pirate->setPrev(nullptr);
    ship->setPirateCount(ship->getPirateCount() - ONE);
    return StatusType::SUCCESS;
}

StatusType Ocean::treason(int sourceShipId, int destShipId)
{
    if (sourceShipId <= ZERO || destShipId <= ZERO ||
        sourceShipId == destShipId)
    {
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Ship> source_ship = findShip(sourceShipId);
    shared_ptr<Ship> dest_ship = findShip(destShipId);

    if (source_ship == nullptr || dest_ship == nullptr ||
        !(source_ship->getPirateCount()))
    {
        return StatusType::FAILURE;
    }

    shared_ptr<Pirate> first_pirate = source_ship->getFirstPirate();
    remove_pirate(first_pirate->getPirateId());

    int source_trasure_modifier = source_ship->getTreasureModifier();
    int new_treasure = first_pirate->getTreasure() + source_trasure_modifier;

    StatusType result = add_pirate(first_pirate->getPirateId(), destShipId, new_treasure);
    return result;
}

StatusType Ocean::update_pirate_treasure(int pirateId, int change)
{
    if (pirateId <= ZERO)
    {
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Pirate> pirate = findPirate(pirateId);

    if (pirate == nullptr)
    {
        return StatusType::FAILURE;
    }

    shared_ptr<Ship> ship = pirate->getShip();
    ship->getMoneyPirates().remove(pirate);
    pirate->setTreasure(pirate->getTreasure() + change);
    ship->getMoneyPirates().insert(pirate);
    return StatusType::SUCCESS;
}

output_t<int> Ocean::get_treasure(int pirateId)
{
    if (pirateId <= ZERO)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    shared_ptr<Pirate> pirate = findPirate(pirateId);
    if (pirate == nullptr)
    {
        return output_t<int>(StatusType::FAILURE);
    }

    int modifier = pirate->getShip()->getTreasureModifier();
    return output_t<int>(pirate->getTreasure() + modifier);
}

output_t<int> Ocean::get_cannons(int shipId)
{
    if (shipId <= ZERO)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    shared_ptr<Ship> ship = findShip(shipId);
    if (ship == nullptr)
    {
        return output_t<int>(StatusType::FAILURE);
    }

    return output_t<int>(ship->getCannonCount());
}

output_t<int> Ocean::get_richest_pirate(int shipId)
{
    if (shipId <= ZERO)
    {
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Ship> ship = findShip(shipId);

    if (ship == nullptr || !(ship->getPirateCount()))
    {
        return output_t<int>(StatusType::FAILURE);
    }

    int richest_pirate_id = ship->getMoneyPirates().root->max_Id.lock()->inner_node->getPirateId();
    return output_t<int>(richest_pirate_id);
}

StatusType Ocean::ships_battle(int shipId1, int shipId2)
{
    if (shipId1 <= ZERO || shipId2 <= ZERO || shipId1 == shipId2)
    {
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Ship> ship1 = findShip(shipId1);
    shared_ptr<Ship> ship2 = findShip(shipId2);

    if (ship1 == nullptr || ship2 == nullptr)
    {
        return StatusType::FAILURE;
    }

    int p1 = ship1->getPirateCount();
    int p2 = ship2->getPirateCount();
    int c1 = ship1->getCannonCount();
    int c2 = ship2->getCannonCount();

    int min_ship1 = (p1 >= c1) ? c1 : p1;
    int min_ship2 = (p2 >= c2) ? c2 : p2;

    if (min_ship1 > min_ship2)
    {
        ship1->setTreasureModifier(ship1->getTreasureModifier() + p2);
        ship2->setTreasureModifier(ship2->getTreasureModifier() - p1);
    }
    else if (min_ship2 > min_ship1)
    {
        ship1->setTreasureModifier(ship1->getTreasureModifier() - p2);
        ship2->setTreasureModifier(ship2->getTreasureModifier() + p1);
    }

    return StatusType::SUCCESS;
}

shared_ptr<AVLTreeNode<Ship>> Ocean::findShipLocation(int shipId)
{
    auto current = ships_tree.root;
    if (current == nullptr)
        return nullptr;
    auto previous = current;
    while (current)
    {
        int curId = current->inner_node->getShipId();

        previous = current;
        if (curId == shipId)
        {
            return current;
        }
        else if (shipId < curId)
        {
            current = current->left_son;
        }
        else
        {
            current = current->right_son;
        }
    }
    return previous;
}

shared_ptr<AVLTreeNode<Pirate>> Ocean::findPirateLocation(int pirateId)
{
    auto current = pirates_tree.root;
    if (current == nullptr)
        return nullptr;
    auto previous = current;
    while (current)
    {
        int curId = current->inner_node->getPirateId();
        previous = current;
        if (curId == pirateId)
        {
            return current;
        }
        else if (pirateId < curId)
        {

            current = current->left_son;
        }
        else
        {

            current = current->right_son;
        }
    }

    return previous;
}

shared_ptr<Ship> Ocean::findShip(int shipId)
{
    auto current = findShipLocation(shipId);
    if (current == nullptr || current->inner_node->getShipId() != shipId)
        return nullptr;
    return current->inner_node;
}

shared_ptr<Pirate> Ocean::findPirate(int pirateId)
{
    auto current = findPirateLocation(pirateId);
    if (current == nullptr || current->inner_node->getPirateId() != pirateId)
        return nullptr;
    return current->inner_node;
}