#pragma once
#include "GameObj.h"
#include "DX_Rectangle.h"

#define ORIENTW 16     ///<the width of the orienter
#define ORIENTH 24    ///<the height of the orienter
#define DISTANCE 5   ///<the number of pointer

static float ball2Orient = 0;

/**
 * @brief the illustration of Orienter class
 *  The subclass of GameObj
 * @param DX_Rectangle class arrays
 * @param isFocus if use the arrow
 *
 */
class Orienter : public GameObj
{
public:
	Orienter(D3DXVECTOR3 in_pos, float in_width, float in_height, float in_alpha);
	~Orienter();
	HRESULT Initialize(LPDIRECT3DDEVICE9 g_pDevice, int type);
	void Update(D3DXVECTOR3 rot);
	void Draw(LPDIRECT3DDEVICE9 g_pDevice);
	void Translation(D3DXVECTOR3 movePos);
	void ORotation(D3DXVECTOR3 in_pos, float in_angle);
	void SetOrienter();

private:
	void TransformPos(void);
	DX_Rectangle pointer[DISTANCE];
	bool isFocus;
};