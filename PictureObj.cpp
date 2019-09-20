/**
 * @file PictureObj.cpp
 * @brief The PictureObj class function
 * This class is for the elements that just show the picture in certain position.
 *
 */
#include "PictureObj.h"
#include "DX_Rectangle.h"


 /**
	 * Construct complex informtion of polygon.
	 *
	 * @param[in] in_pos     position component
	 * @param[in] in_width   width component
	 * @param[in] in_height  height component
	 * @param[in] in_alpha   alpha component
 */
PictureObj::PictureObj(D3DXVECTOR3 in_pos, float in_width, float in_height, float in_alpha)
	:m_pos(in_pos),
	m_width(in_width),
	m_height(in_height),
	m_alpha(in_alpha)
{}
 /**
     * Release the pointer in PictureObj class.
 */
PictureObj::~PictureObj()
{
	bgRect->~DX_Rectangle();
	bg_Texture->Release();
}
/**
	* Get the texture of the PictureObj and init the polygon. return if succeed in creating.
	*
	* @param[in] g_pDevice   The pointer of DirectX9 device.
	* @param[in] type   The type of the object. Depand on the 'type' the object texture and some basic setting may different.
	* @return If the init is success.
	*/
bool PictureObj::Init(LPDIRECT3DDEVICE9 g_pDevice,LPCSTR bgFile)
{
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice,	// デバイスのポインタ
		bgFile,					// ファイルの名前
		&bg_Texture)))
	{
		MessageBox(0, "Init Background texture failed", NULL, NULL);
		return false;
	}
	bgRect = new DX_Rectangle();
	int alpha = m_alpha * 255;
	bgRect->InitRectangle(m_pos.x,m_pos.y,m_width,m_height, 0.0f, 0.0f, 1.0, 1.0, 0, D3DCOLOR_RGBA(255, 255, 255, alpha));
	bgRect->SetAlpha(m_alpha);
	return true;
}
void PictureObj::Update()
{
}
/**
	* Draw the polygon.
	*
	* @param[in] g_pDevice   The pointer of DirectX9 device.
*/
void PictureObj::Draw(LPDIRECT3DDEVICE9 g_pDevice)
{
	g_pDevice->SetTexture(0, bg_Texture);
	bgRect->DrawRectangle(g_pDevice);
}
/**
	* Set the alpha of polygon.
	*
	* @param[in] in_alpha   The alpha of polygon.
*/
void PictureObj::SetAlpha(float in_alpha)
{
	bgRect->SetAlpha(in_alpha);
}