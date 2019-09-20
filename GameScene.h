#pragma once
#include "Scene.h"
#include <vector>
#include "Collision.h"

class Player;
class Enemy;
class Map;
class PictureObj;
class GameObj;

/**
  * @brief The subclass of Scene class
  * The main scene of game.
*/
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	HRESULT Initialize(LPDIRECT3DDEVICE9 g_pDevice);
	void Update(LPDIRECT3DDEVICE9 g_pDevice,float dt);
	void Draw(LPDIRECT3DDEVICE9 g_pDevice);
private:

	Map *g_pMap;                    ///<the pointer of present map
	GameObj *g_pObj;               ///<the pointer of the GameObj class
	std::vector<GameObj *> gamePlayer;   ///<the pointer of vector player class

	int score;    ///<the score of player
	int stageNo;  ///<the prescent stageNo 

	PictureObj *bg;                 ///<background picture
	PictureObj *paceLable;          ///<the remain pace lable
	PictureObj *scoreLable;         ///<the score lable
	
};



