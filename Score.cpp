#include "Score.h"
#include "DX_Rectangle.h"
#include <vector>

namespace Score
{
	namespace
	{
		LPDIRECT3DTEXTURE9 scoreTex = nullptr;  ///<the texture pointer
		DX_Rectangle scoreRect[5];   ///<score polygon array
		int g_nScore = 0;    ///<The total score
	}
	/**
		* Initialize the score.
		* @param[in] g_pDevice The directX9 device pointer.
		* @param[in] pSrcFile The texture file name.
	*/
	void InitScore(LPDIRECT3DDEVICE9 g_pDevice, LPCSTR  pSrcFile)
	{
		if (FAILED(D3DXCreateTextureFromFile(g_pDevice, pSrcFile, &scoreTex)))
		{
			MessageBox(0, "Init scoe texture failed", NULL, NULL);
			return;
		}
	
		for (int i = 0; i < 5; i++)
		{
			scoreRect[i].InitRectangle(SCREENW - 320 + i * 48, 64, 40, 32, 1.0, 0.0, 0.1, 1.0,0,D3DXCOLOR(1.0,1.0,1.0,1.0));
		}
	}
	/**
		* Draw the score.
		* @param[in] g_pDevice The directX9 device pointer.
		* @param[in] bZero Is the score draw by 00000 or 0.
	*/
	void DrawScore(LPDIRECT3DDEVICE9 g_pDevice, bool bZero)
	{
		g_pDevice->SetTexture(0, scoreTex);

		int score = g_nScore;
		if (bZero)
		{
			for (int i = 0; i < 5; i++)
			{
				int num = score % 10;
				scoreRect[i].SetTexture(num * 0.1, 0.0,0);
				score /= 10;
			}
			for (int i = 0; i < 5; i++)
			{
				scoreRect[i].DrawRectangle(g_pDevice);
			}
		}

		else
		{
			int i = 4;
			do
			{
				int num = score % 10;
				scoreRect[i].SetTexture(num * 0.1, 0.0, 0);
				scoreRect[i].DrawRectangle(g_pDevice);
				score /= 10;
				i--;
			} while (score != 0 && i >0);
		}
	}
	/**
		* Add score.
		* @param[in] score 
	*/
	void AddScore(int score)
	{
		g_nScore += score;
	}
	/**
		* Get the total present score.
		* @return int
	*/
	int GetScore(void)
	{
		return g_nScore;
	}
	/**
		* Reset the score to zero and reset the polygon.
	*/
	void ResetScore(void)
	{
		g_nScore = 0;
		for (int i = 0; i < 5; i++)
		{
			scoreRect[i].InitRectangle(SCREENW - 320 + i * 48, 64, 40, 32, 1.0, 0.0, 0.1, 1.0, 0, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}
	/**
		* Uninit score
	*/
	void UninitScore()
	{
		SAFE_RELEASE(scoreTex);
	}
	/**
		* Set the position of score.
		* @param[in] cx The firse center position of the score polygon array.
		* @param[in] cy The firse center position of the score polygon array.
	*/
	void SetScoreRect(float cx,float cy)
	{
		for (int i = 0; i < 5; i++)
		{
			scoreRect[i].UpdateRectangle(cx + i * 48, cy);
		}
	}
}