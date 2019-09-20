#pragma once
#include "d3dApp.h"
#include "sound.h"
#include "stage.h"


namespace Fade
{
	void InitFade(int frame, D3DXCOLOR color, bool bOut);
	void UpdateFade(LPDIRECT3DDEVICE9 g_pDevice);
	void DrawFade(LPDIRECT3DDEVICE9 g_pDevice);
	void SetFade(bool in_fade, SCENE in_scene, SOUND_LABEL sNo);
	void UninitFade();
	bool GetIsFade();
}

