#include "GameApp.h"
/**
* @file The file of this program.
*   This is a simple 2D game by DirectX9.
*   The main concept of the game is to rotating the ball and 
* shoot the ball in the direction as your setted.
*   Break the blocks and get the different power to win the more score and 
* arrive the goal point.
*   The map design used the applition called 'MapWin'.It can easily create the 2D map.
* [Shortage]  
*  >There may be some bugs caused by the judge of the collision.
* [Extention]
*  >Add moving block in the map may be funnier.
* @author nlsysis@localhost HAL Tokyo 2019/09/19
*/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	GameApp theApp(hInstance);

	if (!theApp.Init())
		return 0;

	return theApp.Run();
}