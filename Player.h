#pragma once
#include "GameObj.h"


#define PLAYER_TYPENUM (1)

class Orienter;
/**
 * @brief the illustration of Player class.
 *  The subclass of GameObj,
 *
 * @param  speed Å@The speed of the player.
 * @param  vx      The speed in the X coordiation.
 * @param  vy      The speed in the Y coordiation.
 * @param  pointer The pointer of orienter
 * @param  force   The origin force of ball when shooting
 * @param  radius  The radius of the player
 * @param  preMove The previous position of the player
 * @paramÅ@border  The border position is the position after the moving
 *
 */

class Player : public GameObj
{
public:
	Player(D3DXVECTOR3	in_pos, float in_width, float in_height, int in_alpha);
	~Player();
	HRESULT Initialize(LPDIRECT3DDEVICE9 g_pDevice, int type);
	void Update(Map *map, float time);
	void Draw(LPDIRECT3DDEVICE9 g_pDevice);
	void Move(Map *map, int dir);
	void TransformPos(void);
	void Rotation(bool isClockwise);
	void Shoot();
	void Focus(void);
private:
	float   speed;        ///<player speed
	float   vx;
	float   vy;
	Orienter *pointer;
	float  force;
	float  radius;
	D3DXVECTOR3	preMove;
	D3DXVECTOR3 border;
};

enum PLAYER_STATE
{
	NORMAL=0,

};