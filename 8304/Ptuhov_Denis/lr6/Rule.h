#pragma once
#include "UnitBase.h"
#include "Resourses.h"
#include "Player.h"

struct RuleBase
{
};

struct FastGameRule : RuleBase
{
	FastGameRule();

	void setUnits(std::vector<std::shared_ptr<UnitBase>>& f_units, 
		          std::vector<std::shared_ptr<UnitBase>>& s_units);

	std::vector<std::shared_ptr<UnitBase>>& getCurPlayerUnits();
	size_t getPlayerNumber();
	PtsPair getCurPlayerPts();
	void changePlayer();



private:
	std::shared_ptr<PlayerBase> cur;
	std::vector<std::shared_ptr<UnitBase>> f_units;
	std::vector<std::shared_ptr<UnitBase>> s_units;

	size_t f_pts = 0;
	size_t s_pts = 0;
	size_t s_shtrum_pts = 0;
};



struct MediumGameRule : RuleBase
{
	MediumGameRule();

	void setUnits(std::vector<std::shared_ptr<UnitBase>>& f_units, 
		          std::vector<std::shared_ptr<UnitBase>>& s_units,
				  std::vector<std::shared_ptr<UnitBase>>& t_units);

	size_t getPlayerNumber();
	std::vector<std::shared_ptr<UnitBase>>& getCurPlayerUnits();
	void changePlayer();
	size_t getCurPlayerPts();

private:
	std::shared_ptr<PlayerBase> cur;
	std::vector<std::shared_ptr<UnitBase>> f_units;
	std::vector<std::shared_ptr<UnitBase>> s_units;
	std::vector<std::shared_ptr<UnitBase>> t_units;

	size_t f_pts = 0;
	size_t s_shtrum_pts = 0;
	size_t t_shturm_pts = 0;
};