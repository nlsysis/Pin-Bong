#pragma once
#include "d3dApp.h"

#define EFFECT_MAX 100

class DX_Rectangle;
/**
	* @brief The struct of the effect object.
*/
typedef struct EffectVer_Tag
{
	D3DXVECTOR2 position;  ///<the position of the effect
	D3DCOLOR color;      ///<the color of the effect
	int life;            ///<the life time of the effect
	float bithflame;    ///<the time after birth the effect
	bool bUse;          ///<if the effect is used
	DX_Rectangle    *effectRect;  ///<the polygon of the effect
}Effect;

void Effect_Init(LPDIRECT3DDEVICE9 g_pDevice);
void Effect_Update();
void Effect_Draw(LPDIRECT3DDEVICE9 g_pDevice);
void Effect_UnInit();
void Effect_Create(float x, float y, D3DCOLOR color, int life, float scale);