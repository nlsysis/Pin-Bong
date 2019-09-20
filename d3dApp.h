#pragma once
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <xinput.h>
#include <dinput.h>
#include "GameTimer.h"

#define SCREENW 960
#define SCREENH 540
/**
	* @brief the illustration of D3DApp class
	* The basic class for init the window and init the directx9.
	*
	*
 */
class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();

	HINSTANCE AppInst()const;                 ///<Get the handle instance of application.
	HWND      MainWnd()const;                 ///<Get the handle of main window.
	float     AspectRatio()const;             ///<Getting Width-to-Height Ratio of Screens

	int Run();

	virtual bool Init();                      ///<The parent method needs to initialize the window and Direct3D section.
	virtual void OnResize();                  ///<This parent method needs to be called when the window size changes
	virtual void UpdateScene(float dt) = 0;   ///<Subclasses need to implement this method to update each frame
	virtual void DrawScene() = 0;             ///<Subclasses need to implement this method to render each frame. 
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	
protected:
	bool InitMainWindow();      ///<Window initialization
	bool InitDirect3D();        ///<Direct3D Initialization

	void CalculateFrameStats(); ///<Calculate the number of frames per second and display them in the window

protected:

	HINSTANCE m_hAppInst;        ///<Application instance handle
	HWND      m_hMainWnd;        ///<Main window handle
	bool      m_AppPaused;       ///<Pause the application
	bool      m_Minimized;       ///<Application minimization
	bool      m_Maximized;       ///<Application maximized
	bool      m_Resizing;        ///<Resize the window
	bool	  m_Enable4xMsaa;	 ///<Open 4 times multiple sampling
	UINT      m_4xMsaaQuality;   ///<Quality Level Supported by MSAA


	GameTimer m_Timer;           ///<Timer

	std::string m_MainWndCaption;         ///<Main window title
	int m_ClientWidth;                    ///<Viewport width
	int m_ClientHeight;                   ///<Viewport height

	LPDIRECT3DDEVICE9 m_pd3dDevice;      ///<The pointer of directx9 device
};

/*
	*@brief safe release the pointer.
*/
template<typename T>
void SAFE_RELEASE(T * target)
{
	if (target != nullptr)
	{
		(target)->Release();
		target = nullptr;
	}
}

