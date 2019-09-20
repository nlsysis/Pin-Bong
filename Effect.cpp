#include "Effect.h"
#include "DX_Rectangle.h"

/**
	* Global  
*/
static int tex_effect000;
static Effect g_Effect[EFFECT_MAX];
static bool isUse;
LPDIRECT3DTEXTURE9	  effect_Texture = nullptr;

/**
	*Initialize the effect.
	* @param[in] The directX9 device pointer.
*/
void Effect_Init(LPDIRECT3DDEVICE9 g_pDevice)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effect[i].bithflame = 0.0f;
		g_Effect[i].life = 0;
		g_Effect[i].position.x = 0.0f;
		g_Effect[i].position.y = 0.0f;
		g_Effect[i].bUse = false;
		g_Effect[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		
		g_Effect[i].effectRect = new DX_Rectangle();
		g_Effect[i].effectRect->InitRectangle(g_Effect[i].position.x, g_Effect[i].position.y,
			12,12,0.0,0.0,1.0,1.0,0, g_Effect[i].color);
	}

	/// Load the texture of the effect
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice,	// デバイスのポインタ
		".\\Asset\\effect000.jpg",					// ファイルの名前
		&effect_Texture)))
	{
		MessageBox(0, "Init Background texture failed", NULL, NULL);
	}
}

/**
	* Update the effect.
*/
void Effect_Update()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!g_Effect[i].bUse)
		{
			continue;
		}

		///The bithflame changed and the alpha diminish.
		int age = g_Effect[i].life - g_Effect[i].bithflame;
		g_Effect[i].bithflame *= 1.1;

		if (age <= 0)
		{
			g_Effect[i].bUse = false;
			continue;
		}

		float e = age / (float)g_Effect[i].life;
		D3DXCOLOR color = g_Effect[i].color;
		color.a = e;
		g_Effect[i].color = color;
	}
}

/**
	* Draw the effect.
	* @param[in] The directX9 device pointer.
*/
void Effect_Draw(LPDIRECT3DDEVICE9 g_pDevice)
{
	/// the texture color = source color + destinate color
	g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	g_pDevice->SetTexture(0, effect_Texture);
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!g_Effect[i].bUse)
		{
			continue;
		}

		g_Effect[i].effectRect->SetColor(g_Effect[i].color);
		g_Effect[i].effectRect->DrawRectangle(g_pDevice);

	}

	g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effect[i].effectRect->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	
}
/**
	* Uninit the effect.
	* 
*/
void Effect_UnInit()
{
	SAFE_RELEASE(effect_Texture);
}
/**
	* Set the effect.
	* @param[in] x The center position of the effect.
	* @param[in] y The center position of the effect.
	* @param[in] color The color of the effect.
	* @param[in] life The life time of the effect.
	* @param[in] scale The size of the effect.(not used)
*/
void Effect_Create(float x, float y, D3DCOLOR color, int life, float scale)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].bUse) {
			continue;
		}
		g_Effect[i].bUse = true;
		g_Effect[i].position.x = x;
		g_Effect[i].position.y = y;

		g_Effect[i].color = color;
		g_Effect[i].life = life;
		g_Effect[i].bithflame = 1.0f;
		g_Effect[i].effectRect->UpdateRectangle(x,y);
		break;
	}
}
