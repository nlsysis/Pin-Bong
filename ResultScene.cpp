#include "ResultScene.h"
#include "PictureObj.h"
#include "input.h"
#include "Score.h"
#include "stage.h"

/**
	* The ResultScene class constructor.
*/
ResultScene::ResultScene()
	:titleRect(nullptr), tagAlpha(0.1f), scoreLable(nullptr)
{}
ResultScene::~ResultScene()
{}
/**
	*Initialize the background and other picture resources in result scene.
	* @param[in] g_pDevice The pointer of directx9 device.
	* @return if the initialize is success
*/
HRESULT ResultScene::Initialize(LPDIRECT3DDEVICE9 g_pDevice)
{
	///background ‰Šú‰»
	bg = new PictureObj(D3DXVECTOR3(SCREENW * 0.5, SCREENH * 0.5, 0.0f), SCREENW, SCREENH, 1.0f);
	bg->Init(g_pDevice, ".\\Asset\\titleBG.jpg");

	pressTag = new PictureObj(D3DXVECTOR3(SCREENW * 0.5, SCREENH - 160, 0.0f), 192, 88, tagAlpha);
	pressTag->Init(g_pDevice, ".\\Asset\\startTag.png");
	///initialize the score lable.
	scoreLable = new PictureObj(D3DXVECTOR3(SCREENW * 0.5 - 120, 180.0f, 0.0f), 160.0f, 80.0f, 1.0f);
	scoreLable->Init(g_pDevice, ".\\Asset\\scoreLable.png");
	///set the position to draw the score
	Score::SetScoreRect(SCREENW * 0.5 + 40,180.0f);
	return  S_OK;
}
/**
	* Press the button and change the scene to end or restart.
	* @param[in] g_pDevice The pointer of directx9 device.
	* @param[in] dt The time of the game.
*/
void ResultScene::Update(LPDIRECT3DDEVICE9 g_pDevice, float dt)
{
	if (Keyboard_IsPress(DIK_RETURN))
	{
		SetScene(g_pDevice, SCENE_TITLE);
	}
}
/**
	* Draw elements in result scene.
	* @param[in] g_pDevice The pointer of directx9 device.
*/
void ResultScene::Draw(LPDIRECT3DDEVICE9 g_pDevice)
{
	bg->Draw(g_pDevice);

	//titleRect->Draw(g_pDevice);
	pressTag->Draw(g_pDevice);
	
	scoreLable->Draw(g_pDevice);

	///draw score
	Score::DrawScore(g_pDevice, false);
}