#include "Rule.h"

FastGameRule::FastGameRule()
{
	cur = std::make_shared<Player1>(this);
}

void FastGameRule::setUnits(std::vector<std::shared_ptr<UnitBase>>& f_units, std::vector<std::shared_ptr<UnitBase>>& s_units)
{
	this->f_units = f_units;
	this->s_units = s_units;
}

std::vector<std::shared_ptr<UnitBase>>& FastGameRule::getCurPlayerUnits()
{
	if (cur->getNumber() == 1)
	{

		return f_units;
	}
	return s_units;
}

size_t FastGameRule::getPlayerNumber()
{
	return cur->getNumber();
}

PtsPair FastGameRule::getCurPlayerPts()
{
	if (cur->getNumber() == 1)
		return { f_pts, -1 };
	return { s_pts, (int)s_shtrum_pts };
}

void FastGameRule::changePlayer()
{
	if (cur->getNumber() == 1)
	{
		std::vector<size_t> erse_inds;
		size_t dead_pts = 0;

		for (size_t i = 0; i < s_units.size(); ++i)
		{
			if (s_units[i]->is_dead == true)
			{
				erse_inds.push_back(i);
				++dead_pts;
				continue;
			}

		}

		for (auto& i : erse_inds)
			s_units.erase(s_units.begin() + i);

		f_pts += dead_pts;


		cur = std::make_shared<Player2>(this);
		return;
	}

	std::vector<size_t> erse_inds;
	size_t dead_pts = 0;
	size_t shturm_pts = 0;

	for (size_t i = 0; i < f_units.size(); ++i)
	{
		if (f_units[i]->is_dead == true)
		{
			erse_inds.push_back(i);
			++dead_pts;
			continue;
		}
	}

	for (size_t i = 0; i < s_units.size(); ++i)
	{
		if ((s_units[i]->p.x == 3 && s_units[i]->p.y == 3) || (s_units[i]->p.x == 3 && s_units[i]->p.y == 2) ||
			(s_units[i]->p.x == 2 && s_units[i]->p.y == 3))
			++shturm_pts;
	}

	for (auto& i : erse_inds)
		f_units.erase(f_units.begin() + i);

	s_pts += dead_pts;
	s_shtrum_pts += shturm_pts;

	cur = std::make_shared<Player1>(this);
}

MediumGameRule::MediumGameRule()
{
	cur = std::make_shared<Player1>(this);
}

void MediumGameRule::setUnits(std::vector<std::shared_ptr<UnitBase>>& f_units, std::vector<std::shared_ptr<UnitBase>>& s_units, std::vector<std::shared_ptr<UnitBase>>& t_units)
{
	this->f_units = f_units;
	this->s_units = s_units;
	this->t_units = t_units;
}

size_t MediumGameRule::getPlayerNumber()
{
	return cur->getNumber();
}

std::vector<std::shared_ptr<UnitBase>>& MediumGameRule::getCurPlayerUnits()
{
	int player_num = getPlayerNumber();

	if (player_num == 1)
		return f_units;
	else if (player_num == 2)
		return s_units;
	return t_units;
}

void MediumGameRule::changePlayer()
{
	int player_num = getPlayerNumber();
	if (player_num == 1)
	{
		std::vector<size_t> erse_inds;
		size_t dead_pts = 0;

		for (size_t i = 0; i < s_units.size(); ++i)
		{
			if (s_units[i]->is_dead == true)
			{
				erse_inds.push_back(i);
				++dead_pts;
				continue;
			}

		} 

		for (auto& i : erse_inds)
			s_units.erase(s_units.begin() + i);

		f_pts += dead_pts;

		erse_inds.clear();
		dead_pts = 0;

		for (size_t i = 0; i < t_units.size(); ++i)
		{
			if (t_units[i]->is_dead == true)
			{
				erse_inds.push_back(i);
				++dead_pts;
				continue;
			}

		}

		for (auto& i : erse_inds)
			s_units.erase(s_units.begin() + i);

		f_pts += dead_pts;

		cur = std::make_shared<Player2>(this);
		return;
	}
	else if (player_num == 2)
	{
		size_t shturm_pts = 0;

		for (size_t i = 0; i < s_units.size(); ++i)
		{
			if ((s_units[i]->p.x == 3 && s_units[i]->p.y == 3) || (s_units[i]->p.x == 3 && s_units[i]->p.y == 2) ||
				(s_units[i]->p.x == 2 && s_units[i]->p.y == 3))
				++shturm_pts;
		}

		s_shtrum_pts += shturm_pts;

		cur = std::make_shared<Player3>(this);
		return;
	}


	size_t shturm_pts = 0;

	for (size_t i = 0; i < t_units.size(); ++i)
	{
		if ((t_units[i]->p.x == 3 && t_units[i]->p.y == 3) || (t_units[i]->p.x == 3 && t_units[i]->p.y == 2) ||
			(t_units[i]->p.x == 2 && t_units[i]->p.y == 3))
			++shturm_pts;
	}

	s_shtrum_pts += shturm_pts;

	cur = std::make_shared<Player1>(this);
}

size_t MediumGameRule::getCurPlayerPts()
{
	int player_num = getPlayerNumber();

	if (player_num == 1)
		return f_pts;
	else if (player_num == 2)
		return s_shtrum_pts;
	return t_shturm_pts;
}
