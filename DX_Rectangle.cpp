#include "DX_Rectangle.h"


DX_Rectangle::DX_Rectangle()
{

}
DX_Rectangle::~DX_Rectangle()
{
}
/**
	* Initialize the polygon.
	* @param[in] cx The center X position of the polygon.
	* @param[in] cy The center Y position of the polygon.
	* @param[in] width The width of the polygon.
	* @param[in] height The height of the polygon.
	* @param[in] ltu The left top texture coordinates.
	* @param[in] ltv The left top texture coordinates.
	* @param[in] spriteU The right bottom texture coordinates. 
	* @param[in] spriteV The right bottom texture coordinates. 
	* @param[in] dir If reverse the texture. 0-no,1-yes.
	* @param[in] color The color of the polygon.
*/
void DX_Rectangle::InitRectangle(float cx, float cy, float width, float height, float ltu, float ltv, float spriteU, float spriteV, int dir,D3DCOLOR color)
{

	m_height = height;
	m_width = width;
	m_spriteU = spriteU;
	m_spriteV = spriteV;

	float halfW = m_width * 0.5f;
	float halfH = m_height * 0.5f;

	if (dir == 0)
	{
		m_vertex[0] = { D3DXVECTOR4(cx - halfW,cy + halfH,0.0f,1.0f),color,{ltu,ltv + spriteV} };
		m_vertex[1] = { D3DXVECTOR4(cx - halfW,cy - halfH,0.0f,1.0f),color,{ltu,ltv } };
		m_vertex[2] = { D3DXVECTOR4(cx + halfW,cy + halfH,0.0f,1.0f),color,{ltu + spriteU,ltv + spriteV} };
		m_vertex[3] = { D3DXVECTOR4(cx + halfW,cy - halfH,0.0f,1.0f),color,{ltu + spriteU,ltv } };

	}

	if (dir == 1)
	{
		m_vertex[0] = { D3DXVECTOR4(cx - halfW,cy + halfH,0.0f,1.0f),color,{ltu + spriteU,ltv + spriteV} };
		m_vertex[1] = { D3DXVECTOR4(cx - halfW,cy - halfH,0.0f,1.0f),color,{ltu + spriteU,ltv  } };
		m_vertex[2] = { D3DXVECTOR4(cx + halfW,cy - halfH,0.0f,1.0f),color,{ltu,ltv + spriteV} };
		m_vertex[3] = { D3DXVECTOR4(cx - halfW,cy + halfH,0.0f,1.0f),color,{ltu ,ltv } };
		
	}
	m_center.x = cx;
	m_center.y = cy;
}
/**
	*Move the polygon.
	* @param[in] The move distance in 3 direction.
*/
void DX_Rectangle::TranslationRectangle(D3DXVECTOR3 trans)
{

	for (int i = 0; i < 4; i++)
	{
		m_vertex[i].position.x += trans.x;
		m_vertex[i].position.y += trans.y;
		m_vertex[i].position.z += trans.z;
	}
	m_center.x += trans.x;
	m_center.y += trans.y;
}
/**
	* Rotate the polygon.
	* @param[in] rot The rotation angle in 3 direction.
*/
void DX_Rectangle::RotationRectangle(D3DXVECTOR3 rot)
{
	D3DXVECTOR4 temp;
	if (rot.z != 0.0f)
	{
		for (int i = 0; i < 4; i++)
		{
			temp = m_vertex[i].position - m_center;
			//m_vertex[i].position.x = temp.x * cos(D3DXToRadian(rot.z)) - temp.y * sin(D3DXToRadian(rot.z)) + m_center.x;
			//m_vertex[i].position.y = temp.x * sin(D3DXToRadian(rot.z)) + temp.y * cos(D3DXToRadian(rot.z)) + m_center.y;
			m_vertex[i].position.x = temp.x * cos(rot.z) - temp.y * sin(rot.z) + m_center.x;
			m_vertex[i].position.y = temp.x * sin(rot.z) + temp.y * cos(rot.z) + m_center.y;
			//v_Triangle[i].position.z = trans.z;
		}
	}
	if (rot.y != 0.0f)
	{
		for (int i = 0; i < 4; i++)
		{
			temp = m_vertex[i].position - m_center;
			m_vertex[i].position.x = temp.x * cos(D3DXToRadian(rot.y)) - temp.z * sin(D3DXToRadian(rot.y)) + m_center.x;
			m_vertex[i].position.z = temp.x * sin(D3DXToRadian(rot.y)) + temp.z * cos(D3DXToRadian(rot.y)) + m_center.y;
			//v_Triangle[i].position.z = trans.z;
		}
	}

}
/**
	* Resize the polygon.
	* @param[in] sizePresent The resize precent of the original one in 3 direction.
*/
void DX_Rectangle::ScaleRectangle(D3DXVECTOR3 sizePresent)
{
	D3DXVECTOR4 temp;
	for (int i = 0; i < 4; i++)
	{
		temp = m_vertex[i].position - m_center;
		m_vertex[i].position.x = temp.x * sizePresent.x + m_center.x;
		m_vertex[i].position.y = temp.y * sizePresent.y + m_center.y;
	}

}
/**
	* Draw the polygon.
	* @param[in] device The directx9 device pointer.
*/
void DX_Rectangle::DrawRectangle(LPDIRECT3DDEVICE9 device)
{
	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vertex, sizeof(Vertex2d));
}
/**
	* Set the texture coordinates of the polygon.
	* @param[in] fposU The left top texture coordinates.
	* @param[in] fposV The left top texture coordinates.
	* @param[in] dir If reverse the texture. 0-no,1-yes.
*/
void DX_Rectangle::SetTexture(float fposU, float fposV, int dir)
{
	if (dir == 0)
	{
		m_vertex[0].uv.x = fposU;
		m_vertex[0].uv.y = fposV + m_spriteV;

		m_vertex[1].uv.x = fposU;
		m_vertex[1].uv.y = fposV;

		m_vertex[2].uv.x = fposU + m_spriteU;
		m_vertex[2].uv.y = fposV + m_spriteV;

		m_vertex[3].uv.x = fposU + m_spriteU;
		m_vertex[3].uv.y = fposV;

	}
	///mirror change
	if (dir == 1)
	{
		
		m_vertex[0].uv.x = fposU + m_spriteU;
		m_vertex[0].uv.y = fposV + m_spriteV;

		m_vertex[1].uv.x = fposU + m_spriteU;
		m_vertex[1].uv.y = fposV;

		m_vertex[2].uv.x = fposU;
		m_vertex[2].uv.y = fposV + m_spriteV;

		m_vertex[3].uv.x = fposU;
		m_vertex[3].uv.y = fposV;
	}
}
/**
	* Get the center position of the polygon.
	* @return 
*/
D3DXVECTOR3 DX_Rectangle::GetCenter()
{
	return D3DXVECTOR3(m_center.x, m_center.y, m_center.z);
}
/**
	* Change the position of the polygon.
	* @param[in] cx The center X position of the polygon.
	* @patam[in] cy The center Y position of the polygon.
*/
void DX_Rectangle::UpdateRectangle(float cx, float cy)
{
	float halfW = m_width * 0.5f;
	float halfH = m_height * 0.5f;

	m_vertex[0].position = D3DXVECTOR4(cx - halfW, cy + halfH, 0.0f, 1.0f);
	m_vertex[1].position = D3DXVECTOR4(cx - halfW, cy - halfH, 0.0f, 1.0f);
	m_vertex[2].position = D3DXVECTOR4(cx + halfW, cy + halfH, 0.0f, 1.0f);
	m_vertex[3].position = D3DXVECTOR4(cx + halfW, cy - halfH, 0.0f, 1.0f);
	
	///change the center position.
	m_center.x = cx;
	m_center.y = cy;
}
/**
	* Set the color of the polygon.
	* @param[in] color The color to set.
*/
void DX_Rectangle::SetColor(D3DCOLOR color)
{
	for (int i = 0; i < 4; i++)
	{
		m_vertex[i].color = color;
	}
}
/**
	* Set the alpha of the polygon.
	* @param[in] in_alpha The alpha to set.
*/
void DX_Rectangle::SetAlpha(float in_alpha)
{
	for (int i = 0; i < 4; i++)
	{
		m_vertex[i].position.w = in_alpha;
	}
}

/**
	* Rotation the polygon through the giving center position.
	* @param[in] in_pos The center position of the rotation.
	* @param[in] in_angle The rotation angle.
*/
void DX_Rectangle::Rotation3(D3DXVECTOR3 in_pos, float in_angle)
{
	float halfW = m_width * 0.5f;
	float halfH = m_height * 0.5f;

	m_center.x = in_pos.x;
	m_center.y = in_pos.y;

	m_vertex[0].position.x = (-halfW) * cos(in_angle) - (halfH)* sin(in_angle) + m_center.x;
	m_vertex[0].position.y = (-halfW) * sin(in_angle) + (halfH)* cos(in_angle) + m_center.y;

	m_vertex[1].position.x = (-halfW) * cos(in_angle) - (-halfH)* sin(in_angle) + m_center.x;
	m_vertex[1].position.y = (-halfW) * sin(in_angle) + (-halfH)* cos(in_angle) + m_center.y;

	m_vertex[2].position.x = (halfW)* cos(in_angle) - (halfH)* sin(in_angle) + m_center.x;
	m_vertex[2].position.y = (halfW)* sin(in_angle) + (halfH)* cos(in_angle) + m_center.y;

	m_vertex[3].position.x = (halfW)* cos(in_angle) - (-halfH)* sin(in_angle) + m_center.x;
	m_vertex[3].position.y = (halfW)* sin(in_angle) + (-halfH)* cos(in_angle) + m_center.y;
}

