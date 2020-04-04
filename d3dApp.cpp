#include "d3dApp.h"
#include <iostream>
#include <sstream>

namespace
{
	D3DApp* g_pd3dApp = nullptr;

}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_pd3dApp->MsgProc(hwnd, msg, wParam, lParam);
}


D3DApp::D3DApp(HINSTANCE hInstance)
	: m_hAppInst(hInstance),
	m_MainWndCaption("DirectX9 Initialization"),
	m_ClientWidth(SCREENW),
	m_ClientHeight(SCREENH),
	m_hMainWnd(nullptr),
	m_AppPaused(false),
	m_Minimized(false),
	m_Maximized(false),
	m_Resizing(false),
	m_Enable4xMsaa(true),
	m_4xMsaaQuality(0),
	m_pd3dDevice(nullptr)
{
///the global pointer to call the callback function.
	g_pd3dApp = this;
}

D3DApp::~D3DApp()
{

}

HINSTANCE D3DApp::AppInst()const
{
	return m_hAppInst;
}

HWND D3DApp::MainWnd()const
{
	return m_hMainWnd;
}

float D3DApp::AspectRatio()const
{
	return static_cast<float>(m_ClientWidth) / m_ClientHeight;
}

int D3DApp::Run()
{
	static float currentElapsed = 0.0f;
	const float timer = 60.0f / 1000;
	MSG msg = { 0 };

	m_Timer.Reset();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_Timer.Tick();  //update timer

			if (!m_AppPaused)
			{
				if ((m_Timer.TotalTime() - currentElapsed) > timer - 60.0f * 0.001)
				{
					CalculateFrameStats();
					UpdateScene(m_Timer.TotalTime());
					DrawScene();
					currentElapsed = m_Timer.TotalTime();
				}
			}
			else
			{
				//Sleep(100);
				m_Timer.Stop();
			}
		}
	}

	//gameover
	return (int)msg.wParam;
}

bool D3DApp::Init()
{
	if (!InitMainWindow())
		return false;

	if (!InitDirect3D())
		return false;

	return true;
}

void D3DApp::OnResize()
{
}
/**
	* The callback function.
	* This is for deal the message in the applition.
*/
LRESULT D3DApp::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);  //メッセージを送る　第三、四引数のなかにメッセージの内容がある
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);  //ウインドウを閉じる
		}
		return 0;
	case WM_DESTROY:		//アプリケーション終了
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);  //基本的な動作もサポートする
}
/**
	* Init window.
	* @return if the init is success.
*/
bool D3DApp::InitMainWindow()
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = MainWndProc;  //ウィンドウのコールバック関数ウインドウのメッセージを処理するコールバック関数へのポインタ
	wc.lpszClassName = "D3DWndClassName"; //ウインドウクラスにつける名前
	wc.hInstance = m_hAppInst;   //このクラスのためのウインドウプロシージャがあるインスタンスハンドル
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);  //マウスカーソルのハンドル
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_BACKGROUND + 1); //ウインドウ背景色
//	wc.style = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);
	wc.style = 0;
	wc.hIcon = NULL;
	wc.lpszMenuName = NULL;

	if (!RegisterClass(&wc))   //システムにwcを登録する メモリを申請します
	{
		MessageBox(0, "RegisterClass Failed.", 0, 0);
		return false;
	}

	RECT R = { 0, 0, m_ClientWidth, m_ClientHeight };
	
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	if (m_Maximized == true)
	{
		AdjustWindowRect(&R, WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP, false);
		m_hMainWnd = CreateWindow(
			"D3DWndClassName",
			m_MainWndCaption.c_str(),
			WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			(HWND)NULL,
			(HMENU)NULL,
			m_hAppInst,
			(LPVOID)NULL);
	}
	else
	{
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME), false);
		m_hMainWnd = CreateWindow(
			"D3DWndClassName",
			m_MainWndCaption.c_str(),
			WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME),
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			0,
			0,
			m_hAppInst,
			0);
	}
	if (!m_hMainWnd)
	{
		MessageBox(0, "CreateWindow Failed.", 0, 0);
		return false;
	}


	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);

	return true;
}
/**
	* Init directx3D.
	* @return if the init is success.
*/
bool D3DApp::InitDirect3D()
{
	LPDIRECT3D9  g_pD3D = nullptr;
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) //初期化Direct3Dインターフェース
		MessageBox(m_hMainWnd, TEXT("DirectX初期化失敗した"), TEXT("DirectX初期化"), MB_OK);

	// Check for hardware vp.

	/*D3DCAPS9 caps;
	g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;*/

	D3DDISPLAYMODE dm;
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&dm);
	D3DPRESENT_PARAMETERS d3dpp = {};
	//d3dpp.BackBufferWidth = dm.Width;    //
	//d3dpp.BackBufferHeight = dm.Height;
	//d3dpp.BackBufferFormat = dm.Format;   //バックバッファの種類
	d3dpp.BackBufferWidth = m_ClientWidth;    //
	d3dpp.BackBufferHeight = m_ClientHeight;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;   //バックバッファの種類
	d3dpp.BackBufferCount = 1;        //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;  //デプスバッファ（深度情報）
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;   //デプス16ビット
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hMainWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice);
	if (FAILED(hr))
	{
		MessageBox(m_hMainWnd, TEXT("DirectXデバイス初期化失敗した"), TEXT("DirectX初期化"), MB_OK);
		return false;
	}
	return true;
}
/**
	* Calculate the number of frame in every second and the time to render every frame.
	* Show the result in the window title.
	* 
*/
void D3DApp::CalculateFrameStats()
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;
	frameCnt++;

	if ((m_Timer.TotalTime() - timeElapsed) >= 1.0f)
	{

		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::ostringstream outs;
		outs.precision(6);
		outs << m_MainWndCaption << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << mspf << " (ms)";

		SetWindowText(m_hMainWnd, outs.str().c_str());

		/// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;

	}
}

