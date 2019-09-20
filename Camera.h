#pragma once
#include <DirectXMath.h>
#include "d3dApp.h"

class GameObj;

void InitCamera(float angle, DirectX::XMFLOAT3 scaleFactors);

void Follow(GameObj *following);
void Unfollow();
bool IsFollowing();
void SetTransform(D3DXVECTOR3 &pos);
