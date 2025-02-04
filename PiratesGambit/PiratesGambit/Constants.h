#pragma once
#include<SFML/Graphics.hpp>

const char* const LAND_SPRITE = "ASSETS\\IMAGES\\landTile1.png";
const char* const GRASSY_LAND_SPRITE = "ASSETS\\IMAGES\\landTile.png";
const char* const SAND_SPRITE = "ASSETS\\IMAGES\\sandTile.png";
const char* const WATER_SPRITE = "ASSETS\\IMAGES\\waterTile.png";

const char* const SAND_TL = "ASSETS\\IMAGES\\TL_LAND_SAND.png";
const char* const SAND_TR = "ASSETS\\IMAGES\\TR_LAND_SAND.png";
const char* const SAND_BL = "ASSETS\\IMAGES\\BL_LAND_SAND.png";
const char* const SAND_BR = "ASSETS\\IMAGES\\BR_LAND_SAND.png";

const char* const SAND_FB = "ASSETS\\IMAGES\\BOTTOM_LAND_SAND.png";
const char* const SAND_FT = "ASSETS\\IMAGES\\TOP_LAND_SAND.png";
const char* const SAND_FL = "ASSETS\\IMAGES\\LEFT_LAND_SAND.png";
const char* const SAND_FR = "ASSETS\\IMAGES\\RIGHT_LAND_SAND.png";

const char* const TL_LANDLOCK = "ASSETS\\IMAGES\\TL_LandLocked.png";
const char* const TR_LANDLOCK = "ASSETS\\IMAGES\\TR_LandLocked.png";
const char* const BL_LANDLOCK = "ASSETS\\IMAGES\\BL_LandLocked.png";
const char* const BR_LANDLOCK = "ASSETS\\IMAGES\\BR_LandLocked.png";

const char* const PLAYER = "ASSETS\\IMAGES\\PLAYER\\PLAYER.png";
const char* const PLAYER_DAMAGED = "ASSETS\\IMAGES\\PLAYER\\PLAYER_DAMAGED.png";
const char* const PLAYER_PLASTERED = "ASSETS\\IMAGES\\PLAYER\\PLAYER_PLASTERED.png";
const char* const CANNON_BALL = "ASSETS\\IMAGES\\Pirates\\MiniCannonBall.png";
const char* const HARPOON = "ASSETS\\IMAGES\\Pirates\\MiniHarpoon.png";

const char* const BARREL = "ASSETS\\IMAGES\\GameObjects\\BARREL.png";

//icons
const char* const CANNON_BALL_ICON = "ASSETS\\IMAGES\\ICONS\\CANNON_BALL.png";
const char* const SWORD_ICON = "ASSETS\\IMAGES\\ICONS\\FIGHT.png";
const char* const SHOOT_ICON = "ASSETS\\IMAGES\\ICONS\\SHOOT.png";
const char* const MONEY_ICON = "ASSETS\\IMAGES\\ICONS\\MONEY.png";
const char* const COIN_ICON = "ASSETS\\IMAGES\\ICONS\\COIN.png";
const char* const SKULL_ICON = "ASSETS\\IMAGES\\ICONS\\SKULL.png";


//Borders
const char* const ACTION_BORDER = "ASSETS\\IMAGES\\Borders\\ActionButton.png";
const char* const BULKY_BORDER = "ASSETS\\IMAGES\\Borders\\BulkyBorder.png";


const char* const PIRATE_CAPTAIN = "ASSETS\\IMAGES\\Pirates\\MiniPirateCaptain.png";
const char* const BUCCANEER_SPRITE = "ASSETS\\IMAGES\\Pirates\\MiniPirateCrew.png";
const char* const GUNNER_SPRITE = "ASSETS\\IMAGES\\Pirates\\MiniPirateGunner.png";
const char* const HARPOONER_SPRITE = "ASSETS\\IMAGES\\Pirates\\MiniPirateHarpooner.png";

//PARTICLES
const char* const BLOOD_PARTICLES = "ASSETS\\IMAGES\\Particles\\BLOOD_PARTICLES.png";
const char* const SHOOT_PARTICLES = "ASSETS\\IMAGES\\Particles\\848.png";

//BUILDINGS
const char* const BUILDINGS = "ASSETS\\IMAGES\\Buildings\\Buildings.png";

const char* const BACKGROUND = "ASSETS\\IMAGES\\export.png";

const char* const FONT = "ASSETS\\FONTS\\VarsityTeam-Bold.otf";

const sf::Color GRAY = sf::Color(21, 21, 21);

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

constexpr int CAMERA_WIDTH= 1920 / 2;
constexpr int CAMERA_HEIGHT = 1080 / 2;

constexpr int CHUNK_NODE_ROWS = 32;
constexpr int CHUNK_NODE_COLS = 32;