#include "RemainPace.h"
#include "DX_Rectangle.h"
#include "Fade.h"

namespace RemainPace
{
	namespace
	{
		LPDIRECT3DTEXTURE9 g_paceTex = nullptr;  ///<the texture pointer
		DX_Rectangle paceRect[3];  ///<the pace counter polygon array.
		int g_nPace = 0;   ///<the present pace.
	}
	/**
		* Initialize the Pace.
		* @param[in] g_pDevice The directX9 device pointer.
		* @param[in] pSrcFile The texture file name.
	*/
	void InitPace(LPDIRECT3DDEVICE9 g_pDevice, LPCSTR  pSrcFile)
	{
		D3DXCreateTextureFromFile(g_pDevice, pSrcFile, &g_paceTex);
		for (int i = 0; i < 3; i++)
		{
			paceRect[i].InitRectangle(240 + i * 48, 64, 40, 32, 1.0, 0.0, 0.1, 1.0, 0, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}
	/**
		* Draw the pace.
		* @param[in] g_pDevice The directX9 device pointer.
	*/
	void DrawPace(LPDIRECT3DDEVICE9 g_pDevice)
	{
		g_pDevice->SetTexture(0, g_paceTex);
		if (g_nPace < 0)
			g_nPace = 0;
		int pace = g_nPace;
		int i = 2;
		do
		{
			int num = pace % 10;
			paceRect[i].SetTexture(num * 0.1, 0.0, 0);
			paceRect[i].DrawRectangle(g_pDevice);
			pace /= 10;
			i--;
		} while (pace != 0 && i > 0);
	}
	/**
		* Reduce pace.
		* @param[in] in_pace.
	*/
	void ReducePace(int in_pace)
	{
		
		g_nPace -= in_pace;
	}
	/**
		* Set pace.
		* @param[in] in_pace.
	*/
	void SetPace(int in_pace)
	{
		g_nPace = in_pace;
	}
	/**
		* Get pace.
		* @return g_nPace.
	*/
	int GetPace(void)
	{
		return g_nPace;
	}
	/**
		* Uninit pace.
	*/
	void UninitPace(void)
	{
		SAFE_RELEASE(g_paceTex);
	}
}
