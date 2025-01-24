#pragma once

enum ParentTileType
{
	WATER,
	LAND,
	SAND
};
enum TileType
{
	TR_SAND,
	TL_SAND,
	BR_SAND,
	BL_SAND,
	FT_SAND,
	FB_SAND,
	FR_SAND,
	FL_SAND,
	TR_LL_SAND,
	TL_LL_SAND,
	BR_LL_SAND,
	BL_LL_SAND,
	GRASSY_LAND,
	DEFAULT_LAND,
	DEFAULT_SAND,
	DEFAULT_WATER
};

enum UnitState
{
	IDLE,
	WALK,
	ATTACK,
	DAMAGED,
	DEATH
};

enum BattleState
{
	PREP,
	BATTLE,
	END
};

enum UnitType
{
	MELEE,
	RANGED
};

enum UnitName
{
	EMPTY,
	BUCCANEER,
	GUNNER,
	HARPOONER
};

enum UnitAllegiance
{
	RED_PLAYER,
	BLUE_PLAYER,
	GREEN_PLAYER,
	YELLOW_PLAYER
};