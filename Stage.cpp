#include "stage.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "Fade.h"
#include "sound.h"
#include "Score.h"
#include "RemainPace.h"
/**
	* Global paraments.
*/
Scene *sceneManager = nullptr;
SCENE g_nScene = SCENE_NONE;
int g_stageNo = -1;    ///<the present stage number
bool g_isChangeStage = false;

/**
	* Change the game stage after pass the last one.
	* @param[in] TileMap The quote of the file name of tile tags.
	* @param[in] mapTex  The map texture file name.
	* @param[in] playerPos  The player position.
*/
void SetStage(LPCSTR &TileMap,LPCSTR &mapTex, D3DXVECTOR3 &playerPos)
{
	mapTex = ".\\Asset\\tex.bmp";
	switch (g_stageNo)
	{
	case 0:
		TileMap = ".\\Asset\\map\\t0.txt";
		playerPos = D3DXVECTOR3(59.0f, 155.0f, 0.0f);
		RemainPace::SetPace(10);
		break;
	case 1:
		TileMap = ".\\Asset\\map\\t1.txt";
		playerPos = D3DXVECTOR3(59.0f, 155.0f, 0.0f);
		RemainPace::SetPace(5);
		break;
	case 2:
		TileMap = ".\\Asset\\map\\t2.txt";
		playerPos = D3DXVECTOR3(59.0f, 155.0f, 0.0f);
		RemainPace::SetPace(5);
		break;
	case 3:
		TileMap = ".\\Asset\\map\\t3.txt";
		playerPos = D3DXVECTOR3(59.0f, 155.0f, 0.0f);
		RemainPace::SetPace(5);
		break;
	case 4:
		TileMap = ".\\Asset\\map\\t4.txt";
		playerPos = D3DXVECTOR3(59.0f, 155.0f, 0.0f);
		RemainPace::SetPace(5);
		break;
	case 5:
		TileMap = ".\\Asset\\map\\t5.txt";
		playerPos = D3DXVECTOR3(59.0f, 113.0f, 0.0f);
		RemainPace::SetPace(5);
		break;
	case 6:
		TileMap = ".\\Asset\\map\\t6.txt";
		playerPos = D3DXVECTOR3(59.0f, 155.0f, 0.0f);
		RemainPace::SetPace(5);
		break;
	case 7:
		TileMap = ".\\Asset\\map\\t7.txt";
		playerPos = D3DXVECTOR3(59.0f, 113.0f, 0.0f);
		RemainPace::SetPace(5);
		break;
	case 8:
		TileMap = ".\\Asset\\map\\t8.txt";
		playerPos = D3DXVECTOR3(59.0f, 113.0f, 0.0f);
		RemainPace::SetPace(5);
		break;
	case 9:
		TileMap = ".\\Asset\\map\\t9.txt";
		playerPos = D3DXVECTOR3(59.0f, 113.0f, 0.0f);
		RemainPace::SetPace(8);
		break;
	case 10:
		TileMap = ".\\Asset\\map\\t11.txt";
		playerPos = D3DXVECTOR3(59.0f, 113.0f, 0.0f);
		RemainPace::SetPace(5);
		break;
	}
}
/**
	* Change the scene.
	* @param[in] g_pDevice The directX9 device pointer.
	* @param[in] scene The scene name.
*/
void SetScene(LPDIRECT3DDEVICE9 g_pDevice, SCENE scene)
{
	if (scene == SCENE_GAME && g_stageNo > STAGE_TOTAL - 1)
	{
		Fade::SetFade(true, SCENE_RESULT, SOUND_LABEL_BGM001);
		return;
	}
	if (sceneManager != nullptr)
	{
		sceneManager->~Scene();
	}
	g_nScene = scene;

	switch (scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		g_stageNo = -1;  ///<in test the stage g_stageNo = test stage-1
		Score::ResetScore();
		sceneManager = new TitleScene();
		sceneManager->Initialize(g_pDevice);
		break;
	case SCENE_GAME:
		g_stageNo++;
		sceneManager = new GameScene();
		sceneManager->Initialize(g_pDevice);
		break;
	case SCENE_RESULT:
		sceneManager = new ResultScene();
		sceneManager->Initialize(g_pDevice);
		break;
	}
}

/**
	* Get the pointer of present scene.
	* @return Scene class pointer.
*/
Scene* GetScene(void)
{
	return sceneManager;
}
/**
	* Get the present stage number.
	* @return The number of the stageNo.
*/
int GetStageNo(void)
{
	return g_stageNo;
}
/**
	* Check if the stage changed.
	* @return is changed the stage.
*/
bool GetIsChangeStage(void)
{
	return g_isChangeStage;
}
/**
	* Set to change stage.
	* @param[in] isChange Set the stageChange state.
*/
void SetIsChangeStage(bool isChange)
{
	g_isChangeStage = isChange;
}