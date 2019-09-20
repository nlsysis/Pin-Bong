#pragma once
#include "Scene.h"


class PictureObj;
/**
	* @brief Subclass of scene.
	* Show the result of the game.
*/
class ResultScene : public Scene
{
public:
	ResultScene();
	~ResultScene();
	HRESULT Initialize(LPDIRECT3DDEVICE9 g_pDevice);
	void Update(LPDIRECT3DDEVICE9 g_pDevice, float dt);
	void Draw(LPDIRECT3DDEVICE9 g_pDevice);
private:
	PictureObj *bg;           ///<background
	PictureObj *pressTag;
	PictureObj *titleRect;
	PictureObj *scoreLable;  ///<the lable picture of the score.

	float tagAlpha;       ///<the alpha of the picture.
};