#pragma once
#include "d3dApp.h"

///For calculate the remainPace after moving.
namespace RemainPace
{
	void InitPace(LPDIRECT3DDEVICE9 g_pDevice, LPCSTR  pSrcFile);  
	void DrawPace(LPDIRECT3DDEVICE9 g_pDevice);
	void ReducePace(int in_pace);
	void SetPace(int in_pace);
	int GetPace(void);
	void UninitPace(void);
}
