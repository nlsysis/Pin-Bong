#pragma once
#include "Scene.h"

class PictureObj;
/**
	* @brief The very first scene of the game.
*/
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();
	HRESULT Initialize(LPDIRECT3DDEVICE9 g_pDevice);
	void Update(LPDIRECT3DDEVICE9 g_pDevice, float dt);
	void Draw(LPDIRECT3DDEVICE9 g_pDevice);
private:
	PictureObj *titleRect;   ///<polygon pointer for title
	PictureObj *pressTag;    ///<polygon pointer for press tag
	PictureObj *bg;          ///<polygon pointer for background
	float tagAlpha;          ///<the alpha of press tag.
};