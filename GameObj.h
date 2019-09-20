#pragma once
#include "d3dApp.h"

class DX_Rectangle;
class Map;
/**
 * @brief the illustration of GameObj class
 * The <code>GameObj</code> class represents the basic class
 *contain functions and paraments of the objects of the game.
 *  Actually if there are other characters like enemy or bullet
 *can inherit this class.
 *  In this program it's the basic class of Player and Orienter.
 *
 * @param use    Description of the game object's state.
 * @param pos    Description of the center position of polygon.
 * @param move   Description of the amount of moving in 3 direction.
 * @param rot    Description of the angle of rotation in 3 direction.
 * @param dir    Description of the direction of player (0-up 1-down 2-left 3-right).
 * @param rect   Description of the pointer of polygon.
 * @param spriteUV  Description of the texture UV.
 * @param width  Description of the width of the polygon.
 * @param height Description of the height of the polygon.
 * @param alpha  Description of the alpha of the polygon.
 * @param CountAnim Count the animation number.It's used if the object has the animation.
 * @param Texture The pointer of texture in Directx9.
 * @param tag   If there are different kinds of game object. It can be defined the kind of the object.
 */
class  GameObj
{
public:
	
	GameObj(D3DXVECTOR3	in_pos, float in_width, float in_height, float in_alpha);
	~GameObj();
	
	virtual HRESULT Initialize(LPDIRECT3DDEVICE9 g_pDevice, int type);

	virtual void Update(Map *map, float dt);
	virtual void Draw(LPDIRECT3DDEVICE9 g_pDevice);
	int GetObjTag(void);
	D3DXVECTOR3 GetPosition(void);
	virtual void  SetPosition(D3DXVECTOR3 in_pos);
	int GetDirection();
	float GetRadius();
	bool GetUsed(void);
	void SetUsed(bool in_use);  //set use add
	int GetReverseDir(void);

protected:
	bool                use;				
	D3DXVECTOR3		    pos;				
	D3DXVECTOR3		    move;
	D3DXVECTOR3		    rot;				
	int                 dir;                   
	DX_Rectangle        *rect;

	D3DXVECTOR2           spriteUV;
	float                 width;			    //
	float                 height;			    //
	float                 alpha;				//
	int				      CountAnim;				// アニメーションカウント
	LPDIRECT3DTEXTURE9	  Texture;		    // テクスチャ情報
	int                tag;
};

/**
 * @brief The type of game object
 */
enum GAMEOBJ_TAG
{
	DEFAULT=0,
	TAG_PLAYER,
	TAG_ENEMY,
	TAG_BULLET
};
/**
 * @brief The direction of game object
 */
enum GAMEOBJ_DIR
{
	DIR_UP = 0,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};