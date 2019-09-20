#pragma once
#include "d3dApp.h"

///The function to calculate the score
namespace Score
{
	void InitScore(LPDIRECT3DDEVICE9 g_pDevice, LPCSTR  pSrcFile);  //init the score
	void DrawScore(LPDIRECT3DDEVICE9 g_pDevice, bool bZero); // draw score
	void AddScore(int score);
	int GetScore(void);
	void ResetScore(void);
	void UninitScore(void);
	void SetScoreRect(float cx,float cy);
}