#include "TitleScene.h"
#include "PictureObj.h"
#include "input.h"
#include "Fade.h"
/**
	* The TitleScene class constructor.
*/
TitleScene::TitleScene()
	:titleRect(nullptr),tagAlpha(0.1f)
{
}
/**
	*The TitleScene class destructor.
	*Release the resource in this class.
*/
TitleScene::~TitleScene()
{
	bg->~PictureObj();
	titleRect->~PictureObj();
	pressTag->~PictureObj();
}
/**
	*Initialize the background and other picture resources in title scene.
	* @param[in] g_pDevice The pointer of directx9 device.
	* @return if the initialize is success
*/
HRESULT TitleScene::Initialize(LPDIRECT3DDEVICE9 g_pDevice)
{
	//background 初期化
	bg = new PictureObj(D3DXVECTOR3(SCREENW * 0.5, SCREENH * 0.5, 0.0f), SCREENW, SCREENH, 1.0f);
	bg->Init(g_pDevice, ".\\Asset\\titleBG.jpg");

	//title 初期化
	titleRect = new PictureObj(D3DXVECTOR3(SCREENW * 0.5, SCREENH * 0.5-80, 0.0f), 240, 88, 1.0f);
	titleRect->Init(g_pDevice, ".\\Asset\\title.png");
	
	//
	pressTag = new PictureObj(D3DXVECTOR3(SCREENW * 0.5 , SCREENH - 160, 0.0f), 192, 88, tagAlpha);
	pressTag->Init(g_pDevice, ".\\Asset\\startTag.png");
	return  S_OK;
}
/**
	* Press the button and change the scene.
	* @param[in] g_pDevice The pointer of directx9 device.
	* @param[in] dt The time of the game.
*/
void TitleScene::Update(LPDIRECT3DDEVICE9 g_pDevice, float dt)
{
	static float alphaDir = 0.02;
	static float m_time = 0.0f;
	// Enter押したら、ステージを切り替える
	if (Keyboard_IsPress(DIK_RETURN))
	{
		//SetScene(g_pDevice, SCENE_GAME);
		Fade::SetFade(true, SCENE_GAME, SOUND_LABEL_BGM002);
	}

	/////want to change the alpha of pressTag but failed ///
	////find the solution of how to change texture alpha
	//if (dt > m_time + 1.0)
	//{
	//	m_time = dt;
	//	if (tagAlpha <= 0.1f)
	//	{
	//		alphaDir = 0.002;
	//	}
	//	if (tagAlpha >= 1.0f)
	//	{
	//		alphaDir = -0.002;
	//	}
	//	tagAlpha += alphaDir;
	//	pressTag->SetAlpha(tagAlpha);
	//}
	
}
/**
	* Draw elements in result scene.
	* @param[in] g_pDevice The pointer of directx9 device.
*/
void TitleScene::Draw(LPDIRECT3DDEVICE9 g_pDevice)
{
	bg->Draw(g_pDevice);
	titleRect->Draw(g_pDevice);
	pressTag->Draw(g_pDevice);
}