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
	m_patternList.emplace_back(L"NATK1");
	m_patternList.emplace_back(L"NATK2");
	m_patternList.emplace_back(L"smash");
	m_patternList.emplace_back(L"area360");
	
}

void ZakanPattern::EnterState()
{
	wstring nextState = m_patternList[m_patternIndex];
	SetState(nextState);
	
	++m_patternIndex;
	if (m_patternIndex >= m_patternList.size())
	{
		m_patternIndex = 0;
	}
}

void ZakanPattern::UpdateState()
{
}

void ZakanPattern::ExitState()
{
}
