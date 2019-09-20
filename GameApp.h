#pragma once
#include "d3dApp.h"
/**
	* @brief the illustration of GameApp class
	* The subclass of D3DApp.
	* This is the main part of the game circle.
	*
 */
class GameApp : public D3DApp
{
public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

private:

};


