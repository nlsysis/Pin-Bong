#pragma once
#include "d3dApp.h"

class DX_Rectangle;

/**
 * @brief the illustration of PictureObj class
 *  
 * @param bg_Texture    The pointer of texture in Directx9.
 * @param bgRect        Description of the pointer of polygon.
 * @param m_pos         Description of the center position of polygon.
 * @param m_width       Description of the width of the polygon.
 * @param m_height      Description of the height of the polygon.
 * @param m_alpha       Description of the alpha of the polygon.
 *
 */
class PictureObj
{
public:
	PictureObj(D3DXVECTOR3 in_pos, float in_width, float in_height, float in_alpha);
	~PictureObj();
	bool Init(LPDIRECT3DDEVICE9 g_pDevice, LPCSTR bgFile);
	void Update();
	void Draw(LPDIRECT3DDEVICE9 g_pDevice);
	void SetAlpha(float in_alpha);
private:
	LPDIRECT3DTEXTURE9	  bg_Texture;
	DX_Rectangle          *bgRect;
	D3DXVECTOR3           m_pos;
	float                 m_width;
	float                 m_height;
	float                 m_alpha;
};
