#pragma once
#include "Prebuild.h"
#include "CConfig.cpp"
#include "BDSAPI.hpp"
#include "Guild.cpp"
using namespace std;
class Land {
public:
	bool static isLandOwned(string landid) {
		return CConfig::GetValueString("Land", landid, "guild", "NaN") != "NaN";
	}

	string static getLandOwner(string landid) {
		return CConfig::GetValueString("Land", landid, "guild", "NaN");
	}

	bool static canLandPvP(string landid, Player* attacker, Player* attackon) {
		if (CConfig::GetValueInt("Land", landid, "pvp", 0) == 1) return true;
		if (Guild::isInGuild(attackon->getNameTag(), CConfig::GetValueString("Land", landid, "guild", "FutureCraft����Ա"))) return false;
		return true;
	}

	void static GiveLand(string landid, string guild) {
		CConfig::SetValueString("Land", landid, "guild", guild);
		CConfig::SetValueString("Land", landid, "pvp", "0");
		CConfig::SetValueString("Land", landid, "modblock", "0");
	}

	bool static canLandModifyBlock(string landid, Player* breaker) {
		if (Guild::isInGuild(breaker->getNameTag(), CConfig::GetValueString("Land", landid, "guild", "FutureCraft����Ա")) || CConfig::GetValueInt("Land", landid, "modblock", 0) == 1 || !Land::isLandOwned(landid)) return true;
		return false;
	}

	string static BlockChunckId(BPos3* positon) {
		int xc = positon->x / 16;
		int zc = positon->z / 16;
		return intToString(xc) + "," + intToString(zc);
	}
	string static PlayerChunckId(Vec3* positon) {
		int xc = positon->x / 16;
		int zc = positon->z / 16;
		return intToString(xc) + "," + intToString(zc);
	}
private:
	string static intToString(int v)
	{
		return std::to_string(v);
	}
};