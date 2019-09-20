#include "DX_Font.h"

ID3DXFont*     g_pFont;
RECT formatRect;

/// Init font
HRESULT InitFont(LPDIRECT3DDEVICE9 gDevice,const HWND hWnd)
{
	if (FAILED(D3DXCreateFont(gDevice, 36, 0, 0, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, ("‚l‚r ‚oƒSƒVƒbƒN"), &g_pFont)))
		return E_FAIL;
	GetClientRect(hWnd, &formatRect);
	return S_OK;
}
/// Draw font
void DrawFont(LPDIRECT3DDEVICE9 gDevice, LPCSTR words,int len)
{
	g_pFont->DrawText(NULL,words ,len, &formatRect, DT_TOP | DT_RIGHT, D3DCOLOR_XRGB(255, 39, 136));
}
