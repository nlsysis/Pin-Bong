#pragma once
#include "d3dApp.h"
/**
	*@brief The basic class of every scene.
*/
class Scene
{
public:
	Scene();
	~Scene();
	virtual HRESULT Initialize(LPDIRECT3DDEVICE9 g_pDevice);
	virtual void Update(LPDIRECT3DDEVICE9 g_pDevice, float dt);
	virtual void Draw(LPDIRECT3DDEVICE9 g_pDevice);
};