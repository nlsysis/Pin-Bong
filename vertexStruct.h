#pragma once
#include <d3d9.h>
#include <d3dx9.h>
/**
	* @brief The struct of the 2d vertex.
*/
struct Vertex2d
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
};
/**
	* @brief The struct of the 3d vertex.
	* The alpha and color adjuct by light and material.
*/
struct Vertex3d
{
	D3DXVECTOR3 position;   //FVF xyz in 3 xyzw in 4
	D3DXVECTOR3 normal;
	D3DXVECTOR2 uv;
};

/// The render way of 2d vertex
const DWORD FVF_VERTEX_2D = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
/// The render way of 3d vertex
const DWORD FVF_VERTEX_3D = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
