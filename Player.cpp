#include "Player.h"
#include "DX_Rectangle.h"
#include "Orienter.h"
#include "DX_Font.h"
#include "Camera.h"
#include "Score.h"
#include "stage.h"
#include "sound.h"
#include "Collision.h"
#include "Map.h"
#include "Effect.h"
#include "Explosion.h"
#include "RemainPace.h"

const LPCSTR  playerTex[PLAYER_TYPENUM] = { ".\\Asset\\ball2.tga" };
int tileNo;
/**
	* Construct complex informtion of polygon.
	*
	* @param[in] in_pos     position component
	* @param[in] in_width   width component
	* @param[in] in_height  height component
	* @param[in] in_alpha   alpha component
*/

Player::Player(D3DXVECTOR3	in_pos, float in_width, float in_height, int in_alpha)
	:speed(3.0f),vx(0),vy(0), pointer(nullptr),
	GameObj(in_pos, in_width, in_height, in_alpha),force(10.0f)
	
{
}

Player::~Player()
{
	
}
/**
	* Get the texture of the orienter and init the polygon. return if succeed in creating.
	*
	* @param[in] g_pDevice   The pointer of DirectX9 device.
	* @param[in] type   The type of the game object. Depand on the 'type' the object texture and some basic setting may different.
	* @return If the init is success.
*/
HRESULT Player::Initialize(LPDIRECT3DDEVICE9 g_pDevice, int type)
{
	///from `type` to select texture
	switch (type)
	{
	case 0:
		if (FAILED(D3DXCreateTextureFromFile(g_pDevice,
			playerTex[0],
			&Texture)))
		{
			MessageBox(0, "Init player texture failed", NULL, NULL);
			return S_FALSE;
		}
		spriteUV.x = 1.0;
		spriteUV.y = 1.0;
		break;
	}

	rect = new DX_Rectangle();
	rect->InitRectangle(pos.x,pos.y,width,height,0.0f,0.0f, spriteUV.x, spriteUV.y, 0, D3DXCOLOR(1.0, 1.0, 1.0, alpha));

	use = true;
	tag = TAG_PLAYER;

	///set orienterPos and Init orienter
	D3DXVECTOR3 orienterPos;
	ball2Orient = width * 0.5 + ORIENTW * 0.5 + DISTANCE;
	orienterPos.x = pos.x + ball2Orient;
	orienterPos.y = pos.y;
	orienterPos.z = 0;
	pointer = new Orienter(orienterPos,NULL,NULL,0.8);
	pointer->Initialize(g_pDevice,0);

	radius = 0.5 * width;	

	return S_OK;
}
/**
	* After press the button to control the player.
	*
	* @param[in] map   The pointer of map.It's for  test of collision.
	* @param[in] time  The time of the game.
	* 
*/
void Player::Update(Map *map, float time)
{
	if (use)
	{
		///if the player has animation write here
		CountAnim++;
		if (CountAnim % 5 == 0)
		{
			rect->SetTexture(3 * spriteUV.x, 3 * spriteUV.y,0);
		}
		/*
		  * @brief To judge whether the player will collision block after moving.
		  * Because the player will move in different directions.So the border will change according of this.
		*/
		preMove = move;
		border = pos;
		D3DXVECTOR3 borderLXY = border;   ///<the left border after moving
		D3DXVECTOR3 borderRXY = border;   ///<the right border after moving
		if (preMove.x > 0)
		{
			border.x += preMove.x + radius;
			borderLXY.x = border.x;
			borderLXY.y = border.y - radius;
			borderRXY.x = border.x;
			borderRXY.y = border.y + radius;
		}
		if (preMove.x < 0)
		{
			border.x += preMove.x - radius;
			borderLXY.x = border.x;
			borderLXY.y = border.y - radius;
			borderRXY.x = border.x;
			borderRXY.y = border.y + radius;
		}
		if(isHitObstacle(borderLXY, map) || isHitObstacle(borderRXY, map) && isHitObstacle(border, map))
		{
			move = preMove;
			int tileNo = map->GetTileNo(border);
			switch (tileNo)
			{
				///hit the block tagged in HEART. Add the pace and vanish the block.
			case HEART:
				RemainPace::ReducePace(-1);
				map->VanishBlock(tileNo);
				break;
				///hit the block tagged in PURPLE. Add the score and vanish the block.
			case PURPLE:
				move.x *= -0.2f;
				move.y *= 0.6f;
				Score::AddScore(1);
				map->VanishBlock(tileNo);
				break;
				///hit the block tagged in GRAY. Add the score and vanish the block.
			case GRAY:
				move.x *= -1.0f;
				move.y *= 1.0f;
				Score::AddScore(1);
				map->VanishBlock(tileNo);
				break;
				///hit the block tagged in LIGHT_BLUE. Add the score and vanish the block.
			case LIGHT_BLUE:
				move.x *= -0.3f;
				move.y *= 0.2f;
				Score::AddScore(2);
				map->VanishBlock(tileNo);
				break;
				///hit the block tagged in YELLOW. It's the goal of the game.
				///Add score and change to the next stage.
			case YELLOW:
				map->VanishBlock(tileNo);
				Score::AddScore(5);
				///to the next stage
				SetIsChangeStage(true);
				break;
				
				///hit the block tagged in NET. Rebound the player.
			case NET:
				move.x *= -0.7f;
				move.y *= 0.9f;
				break;
				///hit the block tagged in STAR. Add the double score and vanish the block.
			case STAR:
				Score::AddScore(10);
				map->VanishBlock(tileNo);
				break;
				///hit the block tagged in BLUE. Add the score and vanish the block.
			case BLUE:
				move.x -= -1.1f;
				move.y *= 1.1f;
				Score::AddScore(3);
				map->VanishBlock(tileNo);
				break;
				///hit the block tagged in RED. Add the score and vanish the block.
			case RED:
				move.x *= 0.1f;
				move.y *= 0.1f;
				Score::AddScore(5);
				map->VanishBlock(tileNo);
				break;

				///hit the block tagged in WALL. Rebound the player.
			case WALL:
				move.x *= -1.2f;
				move.y *= 1.2f;
				break;
			}
			SetExplosion(pos.x, pos.y); ///<Explosion effect
		}
		else   ///the collision happened in the Y direction
		{
			border.x = pos.x;
			if (preMove.y > 0)
			{
				border.y += preMove.y + radius;
				borderLXY.x = border.x - radius;
				borderLXY.y = border.y;
				borderRXY.x = border.x + radius;
				borderRXY.y = border.y;
			}
			if (preMove.y < 0)
			{
				border.y += preMove.y - radius;
				borderLXY.x = border.x - radius;
				borderLXY.y = border.y;
				borderRXY.x = border.x + radius;
				borderRXY.y = border.y;
			}

			if (isHitObstacle(borderLXY, map) || isHitObstacle(borderRXY, map) && isHitObstacle(border, map))
			{
				move = preMove;
				int tileNo = map->GetTileNo(border);
				switch (tileNo)
				{
					///hit the block tagged in HEART. Add the pace and vanish the block.
				case HEART:
					RemainPace::ReducePace(-1);
					map->VanishBlock(tileNo);
					break;
					///hit the block tagged in PURPLE. Add the score and vanish the block.
				case PURPLE:
					move.y *= -0.2f;
					move.x *= 0.6f;
					map->VanishBlock(tileNo);
					Score::AddScore(1);
					break;
					///hit the block tagged in GRAY. Add the score and vanish the block.
				case GRAY:
					move.x *= 1.0f;
					move.y *= -1.0f;
					Score::AddScore(1);
					map->VanishBlock(tileNo);
					break;
					///hit the block tagged in LIGHT_BLUE. Add the score and vanish the block.
				case LIGHT_BLUE:
					move.y *= -0.3f;
					move.x *= 0.2f;
					Score::AddScore(2);
					map->VanishBlock(tileNo);
					break;
					///hit the block tagged in YELLOW. It's the goal of the game.
					///Add score and change to the next stage.
				case YELLOW:
					map->VanishBlock(tileNo);
					Score::AddScore(5);
					SetIsChangeStage(true);
					break;
					///hit the block tagged in NET. Rebound the player.
				case NET:
					move.y *= -0.7f;
					move.x *= 0.9f;
					break;
					///hit the block tagged in STAR. Add the double score and vanish the block.
				case STAR:
					Score::AddScore(10);
					map->VanishBlock(tileNo);
					break;
					///hit the block tagged in BLUE. Add the score and vanish the block.
				case BLUE:
					move.y *= -1.1f;
					move.x *= 1.1f;
					Score::AddScore(3);
					map->VanishBlock(tileNo);
					break;
					///hit the block tagged in RED. Add the score and vanish the block.
				case RED:
					move.y *= 0.1f;
					move.x *= 0.1f;
					Score::AddScore(5);
					map->VanishBlock(tileNo);
					break;
									
					///hit the block tagged in WALL. Rebound the player.
				case WALL:
					move.x *= 1.2f;
					move.y *= -1.2f;
					break;
				}
				SetExplosion(pos.x, pos.y);  ///<Explosion effect
			}			
		}
	
		///change the player position
		pos.x += move.x;
		pos.y += move.y;
		rect->TranslationRectangle(move);
		Effect_Create(pos.x ,pos.y ,D3DCOLOR_RGBA(255,0,0,200),10,30.0f);  ///<the moving tile effect
		
		pointer->Translation(move);   ///<move the orienter

		if (abs(move.x) <= 1 && abs(move.y) <= 1)
		{
			move.x = 0;
			move.y = 0;
			pointer->SetUsed(true);
		}
		move *= 0.95f;

		///////////for test print the tileNo of now player standing
		tileNo = map->GetTileNo(pos);

	}
}
/**
	* Draw the polygon.
	*
	* @param[in] g_pDevice   The pointer of DirectX9 device.
*/
void Player::Draw(LPDIRECT3DDEVICE9 g_pDevice)
{
	TransformPos();  ///_<if use camera transform the position into the world position
	if (pointer->GetUsed())
	{
		pointer->Draw(g_pDevice);
	}
	GameObj::Draw(g_pDevice);

	///////////////for test print the position of playse
	/*char printPos[50];
	int n = sprintf_s(printPos,"PlayerPosX:%0.1f PlayerPosY:%0.1f\n",pos.x,pos.y);
	DrawFont(g_pDevice,printPos,n);*/

	/*char tilePos[50];
	int s = sprintf_s(tilePos, "mapTileNo:%d", tileNo);
	DrawFont(g_pDevice, tilePos, s);*/
	
}
/**
	* This part is for test. Press the Up arrow button... in the keyboard can control the player.
	*
	* @param[in] map   The pointer of the stage.It's for test can the player moving.
	* @param[in] direction The direction of the player.
*/
void Player::Move(Map *map,int direction)
{
	//border = pos;
	D3DXVECTOR3 borderLXY;
	D3DXVECTOR3 borderRXY;
	switch (direction)
	{
	case DIR_UP:  //<UP
		move.y -= speed;
		//border.y -= height * 0.5;
		borderLXY.y = pos.y - height * 0.5;
		borderLXY.x = pos.x - width * 0.5;
		borderRXY.y = pos.y - height * 0.5;
		borderRXY.x = pos.x + width * 0.5;
		break;
	case DIR_DOWN:
		move.y += speed;
		//border.y += height * 0.5;
		borderLXY.y = pos.y + height * 0.5;
		borderLXY.x = pos.x - width * 0.5;
		borderRXY.y = pos.y + height * 0.5;
		borderRXY.x = pos.x + width * 0.5;
		break;
	case DIR_LEFT:
		move.x -= speed;
		//border.x -= width * 0.5;
		borderLXY.x = pos.x - width * 0.5;
		borderLXY.y = pos.y - height * 0.5;
		borderRXY.x = pos.x - width * 0.5;
		borderRXY.y = pos.y + height * 0.5;
		break;
	case DIR_RIGHT:
		move.x += speed;
		//border.x += width * 0.5;
		borderLXY.x = pos.x + width * 0.5;
		borderLXY.y = pos.y - height * 0.5;
		borderRXY.x = pos.x + width * 0.5;
		borderRXY.y = pos.y + height * 0.5;
		break;
	}

	dir = direction;
	
	//border += move;
	borderLXY += move;
	borderRXY += move;
	if (!isHitObstacle(borderLXY,map) && !isHitObstacle(borderRXY,map))
	{
		pos += move;
		rect->TranslationRectangle(move);
		pointer->Translation(move);
	}

	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

/**
* Rotation the polygon.
*
* @param[in] movePos the move amount of 3 direction.
*/
void Player::Rotation(bool isClockwise)
{
	if (isClockwise)
	{
		rot.z += D3DX_PI / 24;
	}
	else
	{
		rot.z -= D3DX_PI / 24;
	}
	if (rot.z == 2 * D3DX_PI || rot.z == -2 * D3DX_PI)
	{
		rot.z = 0;
	}
	D3DXVECTOR3 pointerPos;
	pointerPos.x = pos.x + ball2Orient * cos(rot.z);
	pointerPos.y = pos.y + ball2Orient * sin(rot.z);
	pointerPos.z = 0;
	pointer->ORotation(pointerPos, rot.z);

}
/**
	* Trasform the player position to world position.
	* This function is for the camera is used.
	* 
*/
void Player::TransformPos()
{
	if (IsFollowing())
	{
		SetTransform(pos);
		rect->UpdateRectangle(pos.x, pos.y);
	}
}

/**
	* Shoot the player in the map.
	*
	* @param[in] map the map of this stage.
*/
void Player::Shoot()
{
	if (pointer->GetUsed())
	{
		move.x = force * cos(rot.z);
		move.y = force * sin(rot.z);
		pointer->SetUsed(false);
	}
	
}
/**
	*  Set the pointer.
	*
*/
void Player::Focus(void)
{
	pointer->SetOrienter();
}
