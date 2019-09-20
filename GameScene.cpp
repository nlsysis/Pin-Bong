#include "GameScene.h"
#include "PictureObj.h"
#include "Map.h"
#include "Player.h"
#include "input.h"
#include "Score.h"
#include "Camera.h"
#include "stage.h"
#include "RemainPace.h"
#include "Fade.h"

/**
 * GameScene class constructor.
*/
GameScene::GameScene()
	:g_pObj(nullptr),
	g_pMap(nullptr)
{

}

/**
	*Release the resource and pointer in GameScene class.
*/
GameScene::~GameScene()
{
	g_pObj->~GameObj();
	//pInput->~DInputClass();
	gamePlayer.clear();
	RemainPace::UninitPace();
}

/**
	* Initiialize the  picture, map, player class.
	* @param[in] g_pDevice The pointer of directx9 device.
	* @return if the init is success.
*/
HRESULT GameScene::Initialize(LPDIRECT3DDEVICE9 g_pDevice)
{
	g_pMap = new Map(24, 13);
	
	///background initialize
	bg = new PictureObj(D3DXVECTOR3(SCREENW * 0.5, SCREENH * 0.5,0.0f), SCREENW, SCREENH,1.0f);
	bg->Init(g_pDevice, ".\\Asset\\bg.png");

	///scoreLable  initialize
	scoreLable = new PictureObj(D3DXVECTOR3(SCREENW - 320.0f, 64.0f, 0.0f), 160.0f, 80.0f, 1.0f);
	scoreLable->Init(g_pDevice, ".\\Asset\\scoreLable.png");
	
	///lasePace initialize
	paceLable = new PictureObj(D3DXVECTOR3(160.0f, 64.0f, 0.0f), 160.0f, 80.0f, 1.0f);
	paceLable->Init(g_pDevice, ".\\Asset\\paceLable.png");

	///pace initialize
	RemainPace::InitPace(g_pDevice, ".\\Asset\\pace.png");
	
	LPCSTR mapTex;
	D3DXVECTOR3 playerPos;
	LPCSTR map1;
	///get the map tiles information
	SetStage(map1, mapTex, playerPos);

	///Map ‰Šú‰»
	g_pMap->InitMap(g_pDevice, map1, mapTex);

	///Player‰Šú‰»
	D3DXVECTOR3 mapLTPos = g_pMap->GetMapLTPos();
	
	g_pObj = new Player(playerPos + mapLTPos, 24, 24, 1.0f);
	if (FAILED(reinterpret_cast<Player*>(g_pObj)->Initialize(g_pDevice, 0)))
	{
		MessageBox(0, "Init player failed", NULL, NULL);
		return S_FALSE;
	}
	
	gamePlayer.push_back(g_pObj);

	return S_OK;
}
/**
	* Update the game scene elements.
	* >1.update the player after press the keyboard
	* >2.update the scene if there are no more stage or pace is less than 0.
	* @param[in] g_pDevice The pointer of directx9 device.
	* @param[in] dt The time of this game.
*/
void GameScene::Update(LPDIRECT3DDEVICE9 g_pDevice,float dt)
{
	if (GetIsChangeStage())
	{
		return;
	}
	
	
	static float shootTime = 0;
	
	//get the player1
	int playerNo = 0;

	///player  direction move depand on the input. This part is for testion collision. if needed can nore off.
	//if (Keyboard_IsPress(DIK_UP))
	//	reinterpret_cast<Player*>(gamePlayer[playerNo])->Move(g_pMap,DIR_UP);

	//if (Keyboard_IsPress(DIK_DOWN))
	//	reinterpret_cast<Player*>(gamePlayer[playerNo])->Move(g_pMap,DIR_DOWN);

	//if (Keyboard_IsPress(DIK_LEFT))
	//	reinterpret_cast<Player*>(gamePlayer[playerNo])->Move(g_pMap,DIR_LEFT);

	//if (Keyboard_IsPress(DIK_RIGHT))
	//	reinterpret_cast<Player*>(gamePlayer[playerNo])->Move(g_pMap,DIR_RIGHT);

	///if press the player shoot
	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		RemainPace::ReducePace(1);    ///<reduce the pace after shoot the ball.
		reinterpret_cast<Player*>(gamePlayer[playerNo])->Shoot();
	}

	if (Keyboard_IsPress(DIK_A))
	{
		///rotatioin the ball
		reinterpret_cast<Player*>(gamePlayer[playerNo])->Rotation(false);
	}
	if (Keyboard_IsPress(DIK_D))
	{
		///rotatioin the ball
		reinterpret_cast<Player*>(gamePlayer[playerNo])->Rotation(true);
	}
	if (Keyboard_IsPress(DIK_P))
	{
		///make the load of the direction.
		reinterpret_cast<Player*>(gamePlayer[playerNo])->Focus();
	}

	for (size_t i = 0; i < gamePlayer.size(); i++)
	{
		gamePlayer[i]->Update(g_pMap, dt);
	}
	
	///if pace less than 0 and the player don't arrive in the goal , then game over.
	if (RemainPace::GetPace() < 0)
	{
		Fade::SetFade(true, SCENE_RESULT, SOUND_LABEL_BGM001);
		return;
	}
}
/**
	* Draw the elements in the game scene.
	* @param[in] g_pDevice The pointer of directx9 device.
*/
void GameScene::Draw(LPDIRECT3DDEVICE9 g_pDevice)
{
	///draw background
	bg->Draw(g_pDevice);

	///draw scoreLable
	scoreLable->Draw(g_pDevice);

	///draw pace lable
	paceLable->Draw(g_pDevice);

	///draw map
	g_pMap->DrawMap(g_pDevice);

	///draw player
	for (size_t i = 0; i < gamePlayer.size(); i++)
	{
		gamePlayer[i]->Draw(g_pDevice);
	}

	///draw present score
	Score::DrawScore(g_pDevice, false);

	///draw pace
	RemainPace::DrawPace(g_pDevice);
	
}