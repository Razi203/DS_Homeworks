#include "pirates24b2.h"
#include <iostream>

// helper functions declarations
void static updateFleetsData(shared_ptr<Fleet> &fleet1, shared_ptr<Fleet> &fleet2);
bool static swap(shared_ptr<Fleet> &fleet1, shared_ptr<Fleet> &fleet2,
				 shared_ptr<Fleet> &head1, shared_ptr<Fleet> &head2);
void static payUp(shared_ptr<Pirate> &pirate1, shared_ptr<Pirate> &pirate2,
				  shared_ptr<Fleet> &fleet1, shared_ptr<Fleet> &fleet2,
				  shared_ptr<Fleet> &head1, shared_ptr<Fleet> &head2);

// Class methods

oceans_t::oceans_t() = default;

oceans_t::~oceans_t() = default;

StatusType oceans_t::add_fleet(int fleetId)
{
	if (fleetId <= ZERO)
	{
		return StatusType::INVALID_INPUT;
	}
	shared_ptr<Fleet> current_fleet;
	try
	{
		current_fleet = fleets.insert(fleetId);
	}
	catch (std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	if (current_fleet == nullptr)
	{
		return StatusType::FAILURE;
	}

	return StatusType::SUCCESS;
}

StatusType oceans_t::add_pirate(int pirateId, int fleetId)
{
	if (fleetId <= ZERO || pirateId <= ZERO)
	{
		return StatusType::INVALID_INPUT;
	}

	shared_ptr<Fleet> current_fleet = fleets.get(fleetId);

	if (current_fleet == nullptr || !current_fleet->isAccessable())
	{
		return StatusType::FAILURE;
	}

	shared_ptr<Pirate> current_pirate;
	try
	{
		current_pirate = pirates.insert(pirateId);
	}
	catch (std::bad_alloc &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	if (current_pirate == nullptr)
	{
		return StatusType::FAILURE;
	}
	current_fleet = current_fleet->getHead(current_fleet);
	current_pirate->setPirateFleet(current_fleet);
	int pirates_num = current_fleet->getPiratesNum() + ONE;
	current_fleet->setPiratesNum(pirates_num);
	current_pirate->setPirateRank(pirates_num - current_fleet->getRankModifier());
	return StatusType::SUCCESS;
}

StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
	if (pirateId <= ZERO || salary <= ZERO)
	{
		return StatusType::INVALID_INPUT;
	}

	shared_ptr<Pirate> current_pirate = pirates.get(pirateId);

	if (current_pirate == nullptr)
	{
		return StatusType::FAILURE;
	}

	int current_money = current_pirate->getPirateMoney();
	current_pirate->setPirateMoney(current_money + salary);

	return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{
	if (fleetId <= ZERO)
	{
		return StatusType::INVALID_INPUT;
	}

	shared_ptr<Fleet> current_fleet = fleets.get(fleetId);

	if (current_fleet == nullptr || !current_fleet->isAccessable())
	{
		return StatusType::FAILURE;
	}

	shared_ptr<Fleet> ptr_fleet = current_fleet->getHead(current_fleet);
	int num_ships = ptr_fleet->getShipsNum();
	return output_t<int>(num_ships);
}

output_t<int> oceans_t::get_pirate_money(int pirateId)
{
	if (pirateId <= ZERO)
	{
		return StatusType::INVALID_INPUT;
	}

	shared_ptr<Pirate> current_pirate = pirates.get(pirateId);
	if (current_pirate == nullptr)
	{
		return StatusType::FAILURE;
	}

	int current_money = current_pirate->getPirateMoney();
	return output_t<int>(current_money);
}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{
	if (fleetId1 <= ZERO || fleetId2 <= ZERO || fleetId1 == fleetId2)
	{
		return StatusType::INVALID_INPUT;
	}
	shared_ptr<Fleet> fleet1 = fleets.get(fleetId1);
	shared_ptr<Fleet> fleet2 = fleets.get(fleetId2);
	if (fleet1 == nullptr || fleet2 == nullptr || !fleet1->isAccessable() || !fleet2->isAccessable())
	{
		return StatusType::FAILURE;
	}

	updateFleetsData(fleet1, fleet2);
	return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
	if (pirateId1 <= ZERO || pirateId2 <= ZERO || pirateId1 == pirateId2)
	{
		return StatusType::INVALID_INPUT;
	}

	auto pirate1 = pirates.get(pirateId1);
	auto pirate2 = pirates.get(pirateId2);

	if (pirate1 == nullptr || pirate2 == nullptr)
	{
		return StatusType::FAILURE;
	}

	auto fleet1 = pirate1->getPirateFleet();
	auto fleet2 = pirate2->getPirateFleet();
	auto head1 = fleet1->getHead(fleet1);
	auto head2 = fleet2->getHead(fleet2);

	if (head1->getFleetId() != head2->getFleetId())
	{
		return StatusType::FAILURE;
	}
	payUp(pirate1, pirate2, fleet1, fleet2, head1, head2);
	return StatusType::SUCCESS;
}

// Helper functions

/**
 * updated all nescassary data after fleets unite
 */
void static updateFleetsData(shared_ptr<Fleet> &fleet1, shared_ptr<Fleet> &fleet2)
{
	auto head1 = fleet1->getHead(fleet1);
	auto head2 = fleet2->getHead(fleet2);
	bool swapped = swap(fleet1, fleet2, head1, head2); // checks and swaps if needed

	int ships_num1 = head1->getShipsNum(), ships_num2 = head2->getShipsNum();
	int pirates_num1 = head1->getPiratesNum(), pirates_num2 = head2->getPiratesNum();
	int modifier1 = head1->getRankModifier(), modifier2 = head2->getRankModifier();

	head2->setFleetFather(head1);
	head1->setShipsNum(ships_num1 + ships_num2);
	head1->setPiratesNum(pirates_num1 + pirates_num2);
	if (pirates_num1 > pirates_num2 || (pirates_num1 == pirates_num2 && !swapped))
	{
		head2->setRankModifier(modifier2 + pirates_num1 - modifier1);
		fleet2->setAccessable(false);
	}
	else
	{
		head1->setRankModifier(modifier1 + pirates_num2);
		head2->setRankModifier(modifier2 - modifier1 - pirates_num2);
		fleet1->setAccessable(false);
	}
}

/**
 * swaps the fleets if needed
 */
bool static swap(shared_ptr<Fleet> &fleet1, shared_ptr<Fleet> &fleet2,
				 shared_ptr<Fleet> &head1, shared_ptr<Fleet> &head2)
{
	if (head1->getShipsNum() < head2->getShipsNum())
	{
		auto temp = head1;
		head1 = head2;
		head2 = temp;

		temp = fleet1;
		fleet1 = fleet2;
		fleet2 = temp;

		return true;
	}
	return false;
}

/**
 * decides which pirate to pay to the other
 */
void static payUp(shared_ptr<Pirate> &pirate1, shared_ptr<Pirate> &pirate2,
				  shared_ptr<Fleet> &fleet1, shared_ptr<Fleet> &fleet2,
				  shared_ptr<Fleet> &head1, shared_ptr<Fleet> &head2)
{
	int rank1 = pirate1->getPirateRank() + fleet1->getRankModifier();
	if (fleet1 != head1)
		rank1 += head1->getRankModifier();
	int rank2 = pirate2->getPirateRank() + fleet2->getRankModifier();
	if (fleet2 != head2)
		rank2 += head2->getRankModifier();

	std::cout << "pirate " << pirate1->getPirateId() << " rank " << rank1 << std::endl;
	std::cout << "pirate " << pirate2->getPirateId() << " rank " << rank2 << std::endl;

	if (rank1 < rank2)
	{
		int money = rank2 - rank1;
		pirate1->setPirateMoney(pirate1->getPirateMoney() + money);
		pirate2->setPirateMoney(pirate2->getPirateMoney() - money);
	}
	else
	{
		int money = rank1 - rank2;
		pirate1->setPirateMoney(pirate1->getPirateMoney() - money);
		pirate2->setPirateMoney(pirate2->getPirateMoney() + money);
	}
}