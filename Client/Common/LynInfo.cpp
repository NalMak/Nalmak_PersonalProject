#include "stdafx.h"
#include "LynInfo.h"



LynInfo::LynInfo(Desc * _desc)
{
	m_runForwardSpeed = _desc->runForwardSpeed;
	m_runBackwardSpeed = _desc->runBackwardSpeed;
	m_jumpPower = _desc->jumpPower;

	m_jumpHalfHeight = _desc->jumpHalfHeight;
	m_halfHeight = _desc->halfHeight;
	m_turningSpeed = _desc->turningSpeed;
}

LynInfo::~LynInfo()
{
}

void LynInfo::Initialize()
{
}

void LynInfo::Update()
{
}
