#pragma once

enum ParentTileType
{
	WATER,
	LAND,
	SAND,
	ROAD
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

enum EnemyDirection
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum UnitState
{
	IDLE,
	WALK,
	ATTACK,
	DAMAGED,
	DEATH
};

enum AllegianceLevel {
	Hostile,
	Neutral,
	Friendly
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
	HARPOONER,
	CANNON,
	BIRD
};

enum ObjectName {
	NO_OBJECT,
	BARREL,
	TREE
};

enum ItemName
{
	NO_ITEM,
	COINS,
	CANNONBALLS
};

enum UnitAllegiance
{
	NONE,
	HUMAN_PLAYER,
	RED_PLAYER,
	BLUE_PLAYER,
	GREEN_PLAYER,
	YELLOW_PLAYER,
	BLACK_PLAYER
};