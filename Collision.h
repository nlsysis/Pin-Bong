#pragma once
#include "d3dApp.h"

class Map;

/**
	*@brief The type of block.
*/
enum BLOCK_TYPE
{
	HEART =1,
	PURPLE,
	GRAY,
	LIGHT_BLUE,
	YELLOW,
	NET,
	STAR,
	BLUE,
	RED,
	WALL
};

bool isHitObstacle(D3DXVECTOR3 border, Map* map);