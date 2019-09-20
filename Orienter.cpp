/**
 * @file Orienter.cpp
 * @brief The Orienter class function
 *
 */
#include "Orienter.h"
#include "Camera.h"


const LPCSTR orienterTex = { ".\\Asset\\orienter2.tga" };
/**
	* Construct complex informtion of polygon.
	*
	* @param[in] in_pos     position component
	* @param[in] in_width   width component
	* @param[in] in_height  height component
	* @param[in] in_alpha   alpha component
*/
Orienter::Orienter(D3DXVECTOR3	in_pos, float in_width, float in_height, float in_alpha)
	:GameObj(in_pos, ORIENTW, ORIENTH, in_alpha)
{

}
Orienter::~Orienter()
{
}
/**
	* Get the texture of the orienter and init the polygon. return if succeed in creating.
	*
	* @param[in] g_pDevice   The pointer of DirectX9 device.
	* @param[in] type   The type of the game object. Depand on the 'type' the object texture and some basic setting may different.
	* @return If the init is success.
	*/
HRESULT Orienter::Initialize(LPDIRECT3DDEVICE9 g_pDevice, int type)
{
	///load the orienter texture
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice,	// デバイスのポインタ
		orienterTex,					// ファイルの名前
		&Texture)))
	{
		MessageBox(0, "Init orient texture failed", NULL, NULL);
		return S_FALSE;
	}
	///Init the polygon of the orienter
	rect = new DX_Rectangle();
	rect->InitRectangle(pos.x, pos.y, width, height, 0.0f, 0.0f, 1.0, 1.0, 0, D3DXCOLOR(1.0, 1.0, 1.0, alpha));

	use = true;
	isFocus = false;
	return S_OK;
}
void Orienter::Update(D3DXVECTOR3 in_rot)
{
	
}
/**
	* Draw the polygon.
	*
	* @param[in] g_pDevice   The pointer of DirectX9 device.
	*/
void Orienter::Draw(LPDIRECT3DDEVICE9 g_pDevice)
{
	if (use)
	{
		TransformPos();
		GameObj::Draw(g_pDevice);

		if (isFocus)
		{
			for (int i = 0; i < DISTANCE; i++)
			{
				pointer[i].DrawRectangle(g_pDevice);
			}
			isFocus = false;
		}
	}
}
/**
* Change the object position to the world position.If use the camera this function can be used.
*
*/
void Orienter::TransformPos(void)
{
	if (IsFollowing())
	{
		SetTransform(pos);
		rect->UpdateRectangle(pos.x, pos.y);
	}
}
/**
*  Move the polygon.
*
* @param[in] movePos the move amount of 3 direction.
*/
void Orienter::Translation(D3DXVECTOR3 movePos)
{
	rect->TranslationRectangle(movePos);
}
/**
*  If press P,set the pointer.
*
*/
void Orienter::SetOrienter()
{
	for (int i = 0; i < DISTANCE; i++)
	{
		pointer[i] = *rect;
		pointer[i].TranslationRectangle(D3DXVECTOR3(24 * cos(rot.z) * (i + 1), 24 * sin(rot.z) * (i + 1),0.0f));
	}
	isFocus = true;
}

/**
*  Rotation the orienter.
*
*  @param[in] in_pos The center position of the player.
*  @param[in] in_angle The angle of ratation.
*/
void Orienter::ORotation(D3DXVECTOR3 in_pos, float in_angle)
{
	rect->Rotation3(in_pos,in_angle);
	rot.z = in_angle;
}
