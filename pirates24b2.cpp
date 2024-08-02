#include "pirates24b2.h"

oceans_t::oceans_t()
{
	// TODO: Your code goes here
}

oceans_t::~oceans_t()
{
	// TODO: Your code goes here
}

StatusType oceans_t::add_fleet(int fleetId)
{
	if (fleetId <= ZERO)
	{
		return StatusType::INVALID_INPUT;
	}
	shared_ptr<Fleet> current_fleet = fleets.insert(fleetId);
	if (current_fleet != nullptr)
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

	if (current_fleet == nullptr || (current_fleet != nullptr && !current_fleet->isAccessable()))
	{
		return StatusType::FAILURE;
	}

	shared_ptr<Pirate> current_pirate = pirates.insert(pirateId);

	if (current_pirate != nullptr)
	{
		return StatusType::FAILURE;
	}
	current_pirate->setPirateFleet(current_fleet);
	int rank_modifier = current_fleet->getRankModifier();
	int pirates_num = current_fleet->getPiratesNum();
	current_fleet->setPiratesNum(pirates_num + ONE);
	current_pirate->setPirateRank(rank_modifier + current_fleet->getPiratesNum());
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

	shared_ptr<Fleet> ptr_fleet = fleets.getHead(current_fleet);
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

	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
