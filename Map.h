#pragma once
#include "d3dApp.h"
#include <fstream>
#include <vector>

#define TILESW 32
#define TILESH 32

class DX_Rectangle;

/**
  * @brief The map class is for setting the block in different stage.
*/
class Map
{
public:
	Map(int in_tileWNum, int in_tileHNum);
	~Map();
	bool InitMap(LPDIRECT3DDEVICE9 g_pDevice, LPCSTR mapFileName, LPCSTR mapTexFileName);
	void UpdateMap();
	void DrawMap(LPDIRECT3DDEVICE9 g_pDevice);
	int GetTileNo(D3DXVECTOR3	nextObjPos);
	D3DXVECTOR3 GetMapLTPos(void);
	void VanishBlock(int in_tileNo);
	void TransformPos(void);
private:
	std::ifstream inFile;      ///<the file stream of mapFileName
	std::vector<int> tilesNo;  ///<the 
	int map_Width;             ///<the width of the map
	int map_Height;            ///<the height of map 
	int tileWNum;             ///<the number of tiles in per width
	int tileHNum;             ///<the number of tiles in per height
	LPDIRECT3DTEXTURE9	  Texture;		  ///<the pointer of texture of the polygon
	DX_Rectangle* g_prect;                ///<it is for initlize vector array 'rect'.
	std::vector<DX_Rectangle*>   rect;     ///<if the tile tag is not 0, then has a rect to draw.
	D3DXVECTOR3	   ltpos;				///<the left top position of the map.(actually the center position of the first tile)
	int presentTileNum;                ///<record the tileNo when there are collision.
	std::vector<int> rect2tileNo;      ///<match the actual tile number in map and the number in tile array(which delete the tiles which tag is 0).
};