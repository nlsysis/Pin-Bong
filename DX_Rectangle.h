#pragma once
#include "d3dApp.h"
#include "vertexStruct.h"

/**
	* The rectangle polygon.The class is the most basic for draw the objects.
*/
class DX_Rectangle
{
public:
	DX_Rectangle();
	~DX_Rectangle();
	void InitRectangle(float cx, float cy, float width, float height, float ltu, float ltv, float spriteU, float spriteV, int dir, D3DCOLOR color);
	D3DXVECTOR3 GetCenter();
	void TranslationRectangle(D3DXVECTOR3 trans);
	void RotationRectangle(D3DXVECTOR3 rot);
	void ScaleRectangle(D3DXVECTOR3 sizePresent);
	void DrawRectangle(LPDIRECT3DDEVICE9 device);
	void SetTexture(float fposU, float fposV, int dir);
	void UpdateRectangle(float cx, float cy);
	void SetColor(D3DCOLOR color);
	void Rotation3(D3DXVECTOR3 in_pos, float in_angle);
	void SetAlpha(float in_alpha);
private:
	Vertex2d m_vertex[4];   ///<the 4 vertex of the rectangle
	D3DXVECTOR4 m_center;   ///<the center position of the rectangle
	float m_height;        ///<the height of the rectangle
	float m_width;         ///<the width of the rectangle
	float m_spriteU;      ///<the right bottom texture coordinates 
	float m_spriteV;       ///<the  right bottom texture coordinates 
};