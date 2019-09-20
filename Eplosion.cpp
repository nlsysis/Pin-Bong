#include "Explosion.h"
#include "DX_Rectangle.h"
/**
	* Global paraments.
*/
LPDIRECT3DTEXTURE9 explossion_tex = nullptr;
Explosion g_explsion[EXPLOSION_MAX];
float spriteU;
float spriteV;

/**
	* Initialize the explosion effect.
	* @param[in] g_pDevice The directX9 pointer.
*/
void InitExplosion(LPDIRECT3DDEVICE9 g_pDevice)
{
	/// Load the texture of explosion
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice,	// デバイスのポインタ
		".\\Asset\\explosion.png",			    	// ファイルの名前
		&explossion_tex)))
	{
		MessageBox(0, "Init Background texture failed", NULL, NULL);
	}
	spriteU = 1.0f / 7;
	spriteV = 1.0f / 2;
	///Initialize the struct of the explosion
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_explsion[i].isExplosion = false;
		g_explsion[i].m_cx = 0.0f;
		g_explsion[i].m_cy = 0.0f;
		g_explsion[i].m_width = 48.0f;
		g_explsion[i].m_height = 48.0f;
		g_explsion[i].spriteNo = 0;
		g_explsion[i].effectRect = new DX_Rectangle();
		g_explsion[i].effectRect->InitRectangle(g_explsion[i].m_cx, g_explsion[i].m_cy, g_explsion[i].m_width, g_explsion[i].m_height,0.0f,0.0f,spriteU,spriteV,0,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	}
}
/**
	* Update explosion.
*/
void UpdateExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (!g_explsion[i].isExplosion)
		{
			continue;
		}
		
		//update the sprite
		g_explsion[i].spriteNo++;
		if (g_explsion[i].spriteNo >= 13)
		{
			g_explsion[i].spriteNo = 0;
			g_explsion[i].isExplosion = false;
			return;
		}
		g_explsion[i].effectRect->SetTexture( (g_explsion[i].spriteNo / 7) * spriteU,  (g_explsion[i].spriteNo % 7 )* spriteV ,0);

	}
}
/**
	* Draw the explosion effect.
	* @param[in] g_pDevice The directX9 pointer.
*/
void DrawExplosion(LPDIRECT3DDEVICE9 g_pDevice)
{
	g_pDevice->SetTexture(0, explossion_tex);
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (!g_explsion[i].isExplosion)
		{
			continue;
		}
		g_explsion[i].effectRect->DrawRectangle(g_pDevice);
	}
}
/**
	* Set the explosion effect.
	* @param[in] px The center position of the explosion
	* @param[in] py The center position of the explosion
*/
void SetExplosion(float px, float py)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_explsion[i].isExplosion)
		{
			continue;
		}
		g_explsion[i].effectRect->UpdateRectangle(px,py);
		g_explsion[i].isExplosion = true;
	}
}