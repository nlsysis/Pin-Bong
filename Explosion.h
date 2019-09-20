#pragma once
#include "d3dApp.h"

#define EXPLOSION_MAX 10

class DX_Rectangle;

/**
	* The struct of the explosion effect.
*/
typedef struct Explosion_Tag
{
	bool isExplosion;    ///<if the explosion is used
	float m_cx;         ///<the center position of the explosion
	float m_cy;         ///<the center position of the explosion
	float m_width;      ///<the width of the explosion polygon
	float m_height;     ///<the height of the explosion polygon
	int spriteNo;      ///<the sprite number of the explosion texture
	DX_Rectangle    *effectRect;         ///<the polygon of the explosion
}Explosion;

void InitExplosion(LPDIRECT3DDEVICE9 m_pd3dDevice);
void UpdateExplosion();
void DrawExplosion(LPDIRECT3DDEVICE9 m_pd3dDevice);
void SetExplosion(float px, float py);