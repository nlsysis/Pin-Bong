#pragma once
#include "d3dApp.h"

#define STAGE_TOTAL 10

class Scene;
/**
	* @brief The list of scene name.
*/
enum SCENE
{
	SCENE_NONE = 0,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT
};

void SetStage(LPCSTR &TileMap, LPCSTR &mapTex, D3DXVECTOR3 &playerPos);
void SetScene(LPDIRECT3DDEVICE9 g_pDevice, SCENE scene);
int GetStageNo(void);
Scene* GetScene(void);
void SetIsChangeStage(bool isChange);
bool GetIsChangeStage(void);


