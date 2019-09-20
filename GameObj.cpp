/**
 * @file GameObj.cpp
 * @brief The basic class of GameObj
 *
 */
#include  "GameObj.h"
#include "DX_Rectangle.h"
#include "Map.h"
/**
	* Construct complex informtion of polygon.
	*
	* @param[in] in_pos     position component
	* @param[in] in_width   width component
	* @param[in] in_height  height component
	* @param[in] in_alpha   alpha component
*/
GameObj::GameObj(D3DXVECTOR3 in_pos, float in_width, float in_height, float in_alpha)
	:use(false),
	rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	alpha(1.0),
	CountAnim(0),
	Texture(nullptr),
	dir(0),
	rect(nullptr),
	tag(DEFAULT)
{
	pos = in_pos;
	width = in_width;
	height = in_height;
	alpha = in_alpha;
	use = false;
}

GameObj::~GameObj()
{
	SAFE_RELEASE(Texture); 
	rect->~DX_Rectangle();
}

/**
	* Get the texture of the game object and init the polygon. return if succeed in creating.
	*
	* @param[in] g_pDevice   The pointer of DirectX9 device.
	* @param[in] type   The type of the game object. Depand on the 'type' the object texture and some basic setting may different.
	* @return If the init is success.
	*/
HRESULT GameObj::Initialize(LPDIRECT3DDEVICE9 g_pDevice, int type)
{
	return S_OK;
}
/**
	* Update the polygon.
	*
	* @param[in] *map   The pointer of map class.
	* @param[in] dt   The game time.
	*/
void GameObj::Update(Map *map, float dt)
{

}
/**
	* Draw the polygon.
	*
	* @param[in] g_pDevice   The pointer of DirectX9 device.
*/
void GameObj::Draw(LPDIRECT3DDEVICE9 g_pDevice)
{
	g_pDevice->SetFVF(FVF_VERTEX_2D);
	if (use)
	{
		///set the texture
		g_pDevice->SetTexture(0, Texture);

		/// Draw the polygon 
		rect->DrawRectangle(g_pDevice);
	}
}
/**
	* Get the game object tag.
	*
	* @return int .
	*
*/
int GameObj::GetObjTag(void)
{
	return tag;
}
/**
	* Get the polygon position.
	*
	* @return  D3DXVECTOR3 The position of game object.
	* 
*/
D3DXVECTOR3 GameObj::GetPosition(void)
{
	return pos;
}
/**
	* Get the game object direction.
	*
	* @return int   The direction of game object.
	* 
*/
int GameObj::GetDirection()
{
	return dir;
}
/**
	* Set the polygon position.
	*
	* @param[in] in_pos   The position you want to set.
	* 
*/
void GameObj::SetPosition(D3DXVECTOR3 in_pos)
{
	pos = in_pos;
	rect->UpdateRectangle(pos.x, pos.y);
}
/**
	* Get the polygon radius.
	*
	* @return float   The radius of polygon.
	*
	*/
float GameObj::GetRadius(void)
{
	if (width >= height)
		return height * 0.5;
	else
		return width * 0.5;

	return 0;
}

/**
	* Get if use the game object.
	*
	* @return bool.
	*
	*/
bool GameObj::GetUsed(void)
{
	return use;
}
/**
	* Get the direction that the gameObject turn to.
	*
	* @return int dir.
	*
	*/
int GameObj::GetReverseDir(void)
{
	switch (dir)
	{
	case DIR_UP:  ///<UP
		dir = DIR_DOWN;
		break;
	case DIR_DOWN:
		dir = DIR_UP;
		break;
	case DIR_LEFT:
		dir = DIR_RIGHT;
		break;
	case DIR_RIGHT:
		dir = DIR_LEFT;
		break;
	}
	return dir;
}
/**
	* Set the polygon isUsed.
	*
	* @param[in] in_use   The state of the game object.
	*
*/
void GameObj::SetUsed(bool in_use)
{
	use = in_use;
}