/******************************************************************************/
/*!
\file	Player.h
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Abstract class to store player
*/
/******************************************************************************/
#pragma once

#include "character.h"
#include "Camera.h"
#include "drawOrder.h"

/******************************************************************************/
/*!
		Class Player:
\brief	Defines a Player class
*/
/******************************************************************************/
class Player :
	public Character
{
protected:
	drawOrder* leftArm;
	drawOrder* rightArm;
	drawOrder* body;
	drawOrder* main;
	drawOrder* trolley;
public:
	Player(void);
	~Player(void);
	
	bool isHoldingChild;
	bool isHoldingTrolley;
	bool isHoldingItem;
	bool paying;
	bool pay;
	int tempNoItemNeedToPay;
	int noOfItemInTrolley;
	Vector3 defaultTrolleyPosition;
	Rotation defaultTrolleyRotation;
	
	//movement
	virtual Vector3 MoveForward(Camera camera, double movingSpeed) = 0;
	virtual Vector3 MoveBackward(Camera camera, double movingSpeed) = 0;
	virtual Vector3 MoveRight(Camera camera, double movingSpeed) = 0;
	virtual Vector3 MoveLeft(Camera camera, double movingSpeed) = 0;
	void DrawIsEqualTo(drawOrder& TempLeftArm, drawOrder& TempRightArm, drawOrder& TempBody, drawOrder& TempMain, drawOrder& TempTrolley);
	virtual void TakingTrolley(const Camera& camera) = 0;
	virtual void ReleaseTrolley(const Vector3& TrolleyCurrentPos) = 0;
	void ResetTrolley();
};

