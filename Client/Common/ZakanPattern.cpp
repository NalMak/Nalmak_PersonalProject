#include "stdafx.h"
#include "ZakanPattern.h"


ZakanPattern::ZakanPattern()
{
}


ZakanPattern::~ZakanPattern()
{
}

void ZakanPattern::Initialize()
{
	//m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"spellSuction");
	//m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"NATK1");
	//m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"spellSuction"); //흡공

	m_phaseIndex = 0;
	SetInteger(L"IsPattern", 1);
	m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"NATK2");
	
	//m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"area360"); //->장판 패턴

	//m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"fireSpellWave"); //->장판 패턴

	m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"fireSpellWave");
	m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"fireSpellWave");

	/*m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"NATK2");
	m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"smash");
	m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"NATK1");
	m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"NATK2");
	m_patternList[ZAKAN_PATTERN_DEFAULT1].emplace_back(L"smash");*/


	m_patternList[ZAKAN_PATTERN_SPECIAL1].emplace_back(L"change");
	m_patternList[ZAKAN_PATTERN_SPECIAL1].emplace_back(L"teleportCenter");
	m_patternList[ZAKAN_PATTERN_SPECIAL1].emplace_back(L"explosion");

	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"NATK1");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"NATK2");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"smash");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"teleport");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"NATK1");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"NATK2");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"backStep");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"area360");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"NATK1");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"NATK2");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"smash");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"backStep");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"powerATK");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"NATK1");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"NATK2");
	m_patternList[ZAKAN_PATTERN_DEFAULT2].emplace_back(L"smash");



	m_patternList[ZAKAN_PATTERN_SPECIAL2].emplace_back(L"teleportCenter");
	m_patternList[ZAKAN_PATTERN_SPECIAL2].emplace_back(L"explosion");


	m_patternList[ZAKAN_PATTERN_DEFAULT3].emplace_back(L"NATK1");
	m_patternList[ZAKAN_PATTERN_DEFAULT3].emplace_back(L"NATK2");
	m_patternList[ZAKAN_PATTERN_DEFAULT3].emplace_back(L"smash");
	m_patternList[ZAKAN_PATTERN_DEFAULT3].emplace_back(L"backStep");
	m_patternList[ZAKAN_PATTERN_DEFAULT3].emplace_back(L"area360");
	m_patternList[ZAKAN_PATTERN_DEFAULT3].emplace_back(L"NATK1");
	m_patternList[ZAKAN_PATTERN_DEFAULT3].emplace_back(L"NATK2");
	m_patternList[ZAKAN_PATTERN_DEFAULT3].emplace_back(L"smash");
	m_patternList[ZAKAN_PATTERN_DEFAULT3].emplace_back(L"powerATK");
	m_patternList[ZAKAN_PATTERN_DEFAULT3].emplace_back(L"splitBlood");
	//m_patternList.emplace_back(L"NATK2");
	//m_patternList.emplace_back(L"smash");
	//m_patternList.emplace_back(L"area360");
	//m_patternList.emplace_back(L"teleportCenter");
	//m_patternList.emplace_back(L"explosion");
	//m_patternList.emplace_back(L"NATK1");
	//m_patternList.emplace_back(L"NATK2");
	//m_patternList.emplace_back(L"smash");
	//m_patternList.emplace_back(L"area360");
	////m_patternList.emplace_back(L"powerATK");
	//m_patternList.emplace_back(L"explosion"); // 천공파열 
	//m_patternList.emplace_back(L"NATK1"); // 천공파열 

	
	
}

void ZakanPattern::EnterState()
{
	SetInteger(L"IsPattern", 1);
	int phase = GetInteger(L"phaseChange");
	if (m_phaseIndex != phase)
	{
		m_phaseIndex = phase;
		m_patternIndex = 0;
	}

	wstring nextState = m_patternList[m_phaseIndex][m_patternIndex];
	SetState(nextState);
	
	++m_patternIndex;
	if (m_patternIndex >= m_patternList[m_phaseIndex].size())
	{
		if (m_phaseIndex == ZAKAN_PATTERN_SPECIAL1 || m_phaseIndex == ZAKAN_PATTERN_SPECIAL2)
		{
			++m_phaseIndex;
			SetInteger(L"phaseChange", m_phaseIndex);
		}
		m_patternIndex = 0;
	}
}

void ZakanPattern::UpdateState()
{
}

void ZakanPattern::ExitState()
{
}
