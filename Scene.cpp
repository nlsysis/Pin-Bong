#include "Scene.h"

Scene::Scene()
{}
Scene::~Scene()
{}
HRESULT Scene::Initialize(LPDIRECT3DDEVICE9 g_pDevice)
{
	return S_OK;
}
void Scene::Update(LPDIRECT3DDEVICE9 g_pDevice, float dt)
{}
void Scene::Draw(LPDIRECT3DDEVICE9 g_pDevice)
{}