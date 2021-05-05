#pragma once

struct BnS_SkillInfo
{
	string stateName;
	string iConName;
	DWORD inputKey;
	UINT animationType;

	bool requiredTarget = false;
	UINT requiredEnergy = 0;
	UINT requiredState;
};