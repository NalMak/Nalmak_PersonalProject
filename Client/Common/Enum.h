#pragma once

enum LYN_STATE
{
	LYN_STATE_PEACE_STANDARD,
	LYN_STATE_BATTLE_STANDARD,
	LYN_STATE_BATTLE_HIDEBLADE,
	LYN_STATE_MAX
};

enum ANIMATION_FIX_PART
{
	ANIMATION_FIX_PART_UPPER,
	ANIMATION_FIX_PART_LOWER,
	ANIMATION_FIX_PART_MAX
};

enum BATTLE_STATE
{
	BATTLE_STATE_WEAK, // 
	BATTLE_STATE_ABNORMALSTATE_RESISTANCE, // 상태이상 저항
	BATTLE_STATE_RESISTANCE, // 상태이상 + 피해 저항
	BATTLE_STATE_GROGI,
	BATTLE_STATE_STUN,
	BATTLE_STATE_DOWN,
	BATTLE_STATE_INVINCIBILITY,
	BATTLE_STATE_MAX
};

enum DAMAGE_FONT_ANIMATION_TYPE
{
	DAMAGE_FONT_ANIMATION_TYPE_FALLING,
	DAMAGE_FONT_ANIMATION_TYPE_EMPHASIS,
	DAMAGE_FONT_ANIMATION_TYPE_MAX
};