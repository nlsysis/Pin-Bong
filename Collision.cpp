#include "Collision.h"
#include "GameObj.h"
#include "Map.h"

/**
	* @brief Check the collided tile tag.
	* @param[in] border The border position of the object.
	* @param[in] map The pointer of map class.
	* @return is colliding the block.
*/
bool isHitObstacle(D3DXVECTOR3 border, Map* map)
{
	int tileNo = map->GetTileNo(border);
	///if collided the block which tag is not 0.
	if (tileNo > 0 && tileNo < 11)
	{
		return true;
	}
	return false;
}
