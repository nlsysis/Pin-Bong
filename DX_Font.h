#pragma once
#include "d3dApp.h"

HRESULT InitFont(LPDIRECT3DDEVICE9 gDevice, HWND hWnd);
void DrawFont(LPDIRECT3DDEVICE9 gDevice, LPCSTR words, int len);

