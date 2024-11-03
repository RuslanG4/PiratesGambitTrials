#pragma once
#include"Includes.h"

//true means neighbour is land

const std::vector<std::vector<std::pair<int, bool>>> sandCornerPatterns 
{
	{{ 1, false}, {3, false}, {4, true }, {6, true}}, //top left corner
	{{ 1, true}, {3, false}, {4, true }, {6, false}}, //top right corner
	{{ 1, true}, {3, true}, {4, false }, {6, false}}, //bottom right corner
	{{ 1, false}, {3, true}, {4, false }, {6, true}}, //bottom left corner
	{{ 1, true}, {2, true} ,{3, false}, {4, true }, {6, true},{7, true}}, //flat top
	{{0, true} ,{ 1, true}, {3, true}, {4, false },{5, true}, {6, true}}, //flat bottom
	{{0, true} ,{ 1, true},{2, true}, {3, true}, {4, true }, {6, false}}, //flat Right
	{{ 1, false}, {3, true}, {4, true },{5, true}, {6, true},{7, true}}, //flat left
	{{ 0, false}, {1, true}, {3, true }, {4,true},{6,true}}, //landLocked TL
	{{ 1, true}, {2, false},{3,true}, { 4, true }, {6,true}}, //landLocked BL
	{{1,true}, { 3, true }, {4,true}, { 5, false }, {6, true }}, //landLocked TR
	{{1,true},{3,true}, { 4, true }, {6, true}, {7, false }}, //landLocked BR
};

const std::vector<std::vector<std::pair<int, bool>>> landPatterns
{
{ {0, true}, {1, true},{2, true}, {3, true},{4, true}, {5, true},{6, true}, {7, true}},
};

const std::vector<std::vector<std::pair<int, bool>>> undesiredLandTiles
{
		{ {0, true}, {1, true},{2, false}, {3, true},{4, false}, {5, false},{6, true}, {7, true}},
	{ {0, false}, {1, true},{2, true}, {3, true},{4, false}, {5, true},{6, true}, {7, false}},
	{ {0, false}, {1, false},{2, true}, {3, true},{4, true}, {5, true},{6, true}, {7, false}},
	{ {0, true}, {1, false},{2, false}, {3, true},{4, true}, {5, false},{6, true}, {7, true}},
		{ {0, true}, {1, true},{2, false}, {3, false},{4, true}, {5, false},{6, true}, {7, true}},
		{ {0, false}, {1, true},{2, true}, {3, false},{4, true}, {5, true},{6, true}, {7, false}},
		{ {0, true}, {1, true},{2, false}, {3, true},{4, true}, {5, false},{6, false}, {7, true}},
		{ {0, false}, {1, true},{2, true}, {3, true},{4, true}, {5, true},{6, false}, {7, false}},
};

const std::vector<std::vector<std::pair<int, bool>>> undesiredTiles
{
	 { {3, false}, {4, false}},
	 {{1, false}, {6, false}},
	{{0, false}, {7, false}},
	{{2, false}, {5, false}},
	{ {0, true}, {1, true},{2, false}, {3, true},{4, false}, {5, false},{6, true}, {7, true}},
	{ {0, false}, {1, true},{2, true}, {3, true},{4, false}, {5, true},{6, true}, {7, false}},
	{ {0, false}, {1, false},{2, true}, {3, true},{4, true}, {5, true},{6, true}, {7, false}},
	{ {0, true}, {1, false},{2, false}, {3, true},{4, true}, {5, false},{6, true}, {7, true}},
	{ {0, true}, {1, true},{2, false}, {3, false},{4, true}, {5, false},{6, true}, {7, true}},
	{ {0, false}, {1, true},{2, true}, {3, false},{4, true}, {5, true},{6, true}, {7, false}},
	{ {0, true}, {1, true},{2, false}, {3, true},{4, true}, {5, false},{6, false}, {7, true}},
	{ {0, false}, {1, true},{2, true}, {3, true},{4, true}, {5, true},{6, false}, {7, false}},
	{ {0, true}, {1, true},{2, true}, {3, true},{4, false}, {5, false},{6, true}, {7, true}},
	{ {0, false}, {1, true},{2, true}, {3, true},{4, false}, {5, true},{6, true}, {7, true}},
	{ {0, true}, {1, false},{2, true}, {3, true},{4, true}, {5, true},{6, true}, {7, false}},
	{ {0, true}, {1, false},{2, true}, {3, true},{4, true}, {5, false},{6, true}, {7, true}},
};

