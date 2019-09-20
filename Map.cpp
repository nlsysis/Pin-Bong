#include "Map.h"
#include "DX_Rectangle.h"
#include "Camera.h"
#include "sound.h"

/**
	* Map class constructor.
	* @param[in] in_tileWNum  The number of tiles per line.
	* @param[in] in_tileHNum  The number of tiles per row.
*/
Map::Map(int in_tileWNum, int in_tileHNum)
	:Texture(nullptr),g_prect(nullptr),
	tileWNum(in_tileWNum), tileHNum(in_tileHNum)
{
	map_Width = tileWNum * TILESW;
	map_Height = tileHNum * TILESH;

	ltpos.x = SCREENW * 0.5 - map_Width * 0.5 - 10;
	ltpos.y = SCREENH * 0.5 - map_Height * 0.5 + 50;
	ltpos.z = 0.0f;
	presentTileNum = 0;
}
Map::~Map()
{

}
/**
	* Initilize the map.Load the texture list and get the tile tag.
	* @param[in] g_pDevice     The pointer of directx9 pointer.
	* @param[in] mapFileName    The file name of the map tile tag.
	* @param[in] mapTexFileName   The file name of the map texture list.
	* @return is the initilize success.
*/
bool Map::InitMap(LPDIRECT3DDEVICE9 g_pDevice, LPCSTR mapFileName,LPCSTR mapTexFileName)
{ 
	/// Load the texture list of the map
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice,	///<device pointer
		mapTexFileName,					///< file name
		&Texture)))
	{
		return false;
	}
	
	/**   @brief Load the tile tag from the file. 
		*The tile tag has connections with the texture list and the attritube of collision
	*/
	inFile.open(mapFileName);
	if (!inFile)
	{
		MessageBox(0, "Init map failed", NULL, NULL);
		return false;
	}
	std::string word;
	while (inFile >> word)
	{
		if(word != ",")
		{
			int x = atoi(word.c_str());
			tilesNo.push_back(x);
		}	
	}
	inFile.close();
	///<store the tileNo in polygon object.
	float textW = 0.1f;
	D3DXVECTOR3 pos = ltpos;
	for (int i = 0; i < tileHNum; i++)
	{
		pos.x = ltpos.x;
		for (int j = 0; j < tileWNum; j++)
		{
			///<if tile tag is not 0,which means not black tile,then initilize a polygon for this tile.
			if (tilesNo[j + i * tileWNum] != 0)
			{
				g_prect = new DX_Rectangle();
				g_prect->InitRectangle(pos.x, pos.y, TILESW, TILESH, (tilesNo[j + i * tileWNum]-1) * textW, 0.0, textW, 1.0,0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				rect.push_back(g_prect);
				rect2tileNo.push_back(j + i * tileWNum);
			}
			pos.x += TILESW;
		}
		pos.y += TILESH;
	}
	return true;

}

void Map::UpdateMap()
{

}
/**
	* Draw the pre tiles to form the map.
	* @param[in] g_pDevice The pointer of the directx9 device.
*/
void Map::DrawMap(LPDIRECT3DDEVICE9 g_pDevice)
{
	g_pDevice->SetFVF(FVF_VERTEX_2D);
	/// テクスチャの設定
	g_pDevice->SetTexture(0, Texture);

	///transform the position to the world if use the camera.
	if (IsFollowing())
	{
		for (size_t i = 0; i < rect.size(); i++)
		{
			D3DXVECTOR3 centerPos = rect[i]->GetCenter();
			SetTransform(centerPos);
			rect[i]->UpdateRectangle(centerPos.x, centerPos.y);
			rect[i]->DrawRectangle(g_pDevice);
		}
		ltpos = rect[0]->GetCenter();
	}
	else
	{
		// ポリゴンの描画
		for (size_t i = 0; i < rect.size(); i++)
		{
			rect[i]->DrawRectangle(g_pDevice);
		}
	}
}
/**
	* @brief Get the tileNo througth the position.
	* @param[in] nextObjPos The position of the object.
	* return The tile tag of the position.
*/
int Map::GetTileNo(D3DXVECTOR3 nextObjPos)
{
	int x = (nextObjPos.x - (ltpos.x - TILESW * 0.5)) / TILESW;
	int y = (nextObjPos.y - (ltpos.y - TILESH * 0.5)) / TILESH;
	presentTileNum = x + y * tileWNum;
	return tilesNo[x + y * tileWNum];
}

/**
	* Get map left top point position.
	* @return Left top point position of the map.
*/
D3DXVECTOR3 Map::GetMapLTPos(void)
{
	return ltpos;
}

/**
	* If use camera, transform the position to world position.
*/
void Map::TransformPos(void)
{
	if (IsFollowing())
	{
		for (size_t i = 0; i < rect.size(); i++)
		{
			D3DXVECTOR3 centerPos = rect[i]->GetCenter();
			SetTransform(centerPos);
			rect[i]->UpdateRectangle(centerPos.x, centerPos.y);
		}
	}
}
/**
	*  Delete the block in the map.
	* @param[in]  The number of the tile in map.
*/
void Map::VanishBlock(int in_tileNo)
{
	///search the tile number in polygon array.
	size_t i;
	for (i = 0; i < rect2tileNo.size(); i++)
	{
		if (rect2tileNo[i] == presentTileNum)
			break;
	}
	rect2tileNo.erase(rect2tileNo.begin() + i);
	rect.erase(rect.begin() + i);
	tilesNo[presentTileNum] = 0;

	///play the sound of collision
	PlaySound(SOUND_LABEL_SE_EXPLOSION1);
}