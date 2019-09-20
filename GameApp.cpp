#include "GameApp.h"
#include "input.h"
#include "DX_Font.h"
#include "Fade.h"
#include "Camera.h"
#include "Score.h"
#include "stage.h"
#include "Sound.h"
#include "Scene.h"
#include "Effect.h"
#include "Explosion.h"
/**
	* Init the D3DApp class.
	*
	* @param[in] hInstance Application instance handle
*/

GameApp::GameApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{

}
/**
	* Uninit the GameApp class.
	*
*/
GameApp::~GameApp()
{
	if(m_pd3dDevice) m_pd3dDevice->Release();
	Effect_UnInit();
	Score::UninitScore();
	Keyboard_Finalize();
}
/**
	* Init the elements before game loop.
	* @return if init is success.
*/
bool GameApp::Init()
{
	if (!D3DApp::Init())
		return false;

	if (FAILED(InitFont(m_pd3dDevice, m_hMainWnd)))
	{
		return false;
	}
	//Camera ‰Šú‰»
    //camera = new Camera(SCREENW,SCREENH,0, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	InitCamera(0, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

	//Input ‰Šú‰»
	if (!Keyboard_Initialize(m_hAppInst,m_hMainWnd))
	{
		MessageBox(0, "Init input failed", NULL, NULL);
		return false;
	}

	//Score ‰Šú‰»
	Score::InitScore(m_pd3dDevice, ".\\Asset\\score.png");
	

	//Fade ‰Šú‰»
	Fade::InitFade(100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), true);

	Effect_Init(m_pd3dDevice);
	InitExplosion(m_pd3dDevice);

	//sound ‰Šú‰»
	if (FAILED(InitSound(m_hMainWnd)))
	{
		return false;
	}
	//SetScene(m_pd3dDevice, SCENE_TITLE);
	PlaySound(SOUND_LABEL_BGM001);

	Fade::SetFade(true,SCENE_TITLE,SOUND_LABEL_BGM001);

	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	
	return true;
}

void GameApp::OnResize()
{
	D3DApp::OnResize();
}
/**
	* Update the frame.
	* @param[in] dt the total time since game started.
*/
void GameApp::UpdateScene(float dt)
{
	Keyboard_Update();
	if (GetIsChangeStage())
	{
		//SetScene(m_pd3dDevice, SCENE_GAME);
		Fade::SetFade(true, SCENE_GAME, SOUND_LABEL_BGM002);
		SetIsChangeStage(false);
	}
	if (!Fade::GetIsFade())   ///<the fade is finished
	{
		GetScene()->Update(m_pd3dDevice, dt);
	}

	Effect_Update();
	UpdateExplosion();
	Fade::UpdateFade(m_pd3dDevice);
	
}
/**
	* Draw the frame.
	* 
*/
void GameApp::DrawScene()
{
	//‰æ–Ê‚ÌƒNƒŠƒA
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	m_pd3dDevice->BeginScene();

	Fade::DrawFade(m_pd3dDevice);
	if (!Fade::GetIsFade())
	{
		GetScene()->Draw(m_pd3dDevice);
	}
	
	Effect_Draw(m_pd3dDevice);
	DrawExplosion(m_pd3dDevice);


	m_pd3dDevice->EndScene();
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

