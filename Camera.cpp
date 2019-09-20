#include "Camera.h"
#include "GameObj.h"

float m_angle;   ///< The angle of the camera 
DirectX::XMFLOAT3 m_scaleFactors;  ///< The size of the screen.

GameObj *m_following = nullptr;  ///<If the camera follow a game object.

/**
	*Initialize the camera.
	* @param[in] angle The angle of the camera.
	* @param[in] scaleFactors The size of screen.
*/
void InitCamera(float angle, DirectX::XMFLOAT3 scaleFactors)
{
	m_angle = angle;
	m_scaleFactors = scaleFactors;
	m_following = nullptr;
}
/**
	* Set the following object.
	* @param[in] following The pointer of the following object.
*/
void Follow(GameObj *following)
{
	m_following = following;
}
/**
	* Release the following object.
*/
void Unfollow()
{
	m_following = nullptr;
}
/**
	* Check the camera is following an object.
	* @return is  follwing.
*/
bool IsFollowing()
{
	return (m_following != nullptr);
}
/**
	* The camera is actually the transform of position to the world.
	* @param[in] pos The quote of the object position.
*/
void SetTransform(D3DXVECTOR3 &pos)
{
	pos.x += -m_following->GetPosition().x + SCREENW * 0.5;
	pos.y += -m_following->GetPosition().y + SCREENH * 0.5;
}

////not using
//void Camera::Update()
//{
//	int cameraX = m_following->GetPosition().x;
//	int cameraY = m_following->GetPosition().y;

//	m_viewMatrix = D3DXMATRIX(
//		m_scaleFactors.x * cos(m_angle), m_scaleFactors.x * sin(m_angle), 0, 0,
//		m_scaleFactors.y * sin(m_angle), m_scaleFactors.y * cos(m_angle), 0, 0,
//		0, 0, m_scaleFactors.z, 0,
//		-cameraX * m_scaleFactors.x * cos(m_angle) + cameraY * m_scaleFactors.y * sin(m_angle),
//		-cameraX * m_scaleFactors.y * sin(m_angle) - cameraY * m_scaleFactors.y * cos(m_angle), 0, 1
//	);
//}
//
