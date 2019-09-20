#include "Fade.h"
#include "DX_Rectangle.h"
///For the fade function

namespace Fade
{
	namespace
	{
		D3DXCOLOR g_FadeColor;
		bool g_bFadeOut = false;
		bool g_bFade = false;
		int g_FadeFrame = 0;
		int g_FadeFrameCount = 0;
		int g_FadeStartFrame = 0;
		SOUND_LABEL g_sno = SOUND_LABEL::SOUND_LABEL_NONE;
		SCENE g_scene = SCENE::SCENE_NONE;
		DX_Rectangle *fadeRect;
		bool isMusicStop = false;
	}
	void InitFade(int frame, D3DXCOLOR color, bool bOut)
	{
		g_FadeColor = color;
		g_FadeFrame = frame;
		g_bFadeOut = bOut;
		g_FadeStartFrame = g_FadeFrameCount;
		g_bFade = false;

		fadeRect = new DX_Rectangle();
		fadeRect->InitRectangle(SCREENW * 0.5, SCREENH *0.5 , SCREENW, SCREENH,0.0,0.0,1.0,1.0,0,g_FadeColor);
	}
	void UpdateFade(LPDIRECT3DDEVICE9 g_pDevice)
	{
		if (g_bFade)
		{
			g_FadeColor.a -= 0.01;
			if (g_FadeColor.a <= 0.0f)
			{
				g_FadeColor.a = 0.0f;
				g_bFade = false;

				SetScene(g_pDevice,g_scene);
				int stageNo = GetStageNo();
				if (stageNo == 0 && g_scene == SCENE::SCENE_GAME || g_scene == SCENE::SCENE_RESULT)
				{
					// BGM’âŽ~
					StopSound();
					isMusicStop = true;
				}
			}
			fadeRect->SetColor(g_FadeColor);
		}
		if (isMusicStop)
		{
			// BGMÄ¶
			if (g_sno > -1)
			{
				PlaySound(g_sno);
				isMusicStop = false;
			}
		}
	}

	void DrawFade(LPDIRECT3DDEVICE9 g_pDevice)
	{
		if (g_bFade)
		{
			g_pDevice->SetFVF(FVF_VERTEX_2D);
			g_pDevice->SetTexture(0,NULL);
			fadeRect->DrawRectangle(g_pDevice);
		}
	}

	void SetFade(bool in_fade, SCENE in_scene,SOUND_LABEL sNo)
	{
	//	g_FadeFrameCount = 0;
		g_bFade = in_fade;
		g_sno = sNo;
		g_scene = in_scene;
		g_FadeColor.a = 1.0f;
	}
	void UninitFade()
	{
		fadeRect->~DX_Rectangle();
	}
	bool GetIsFade()
	{
		return g_bFade;
	}
}