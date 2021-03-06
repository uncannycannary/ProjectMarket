/******************************************************************************/
/*!
\file	ShopperWandererLv2.h
\author Gregory Koh Wen Cong
\par	email: pyroflame11@gmail.com
\brief
Class to store ShopperWandererLv2
*/
/******************************************************************************/
#pragma once

#include "Shopper.h"
#include "DrawOrder.h"

/******************************************************************************/
/*!
		Class ShopperWandererLv2:
\brief	Defines a ShopperWandererLv2 class
*/
/******************************************************************************/
class ShopperWandererLv2 :
	public Shopper
{
private:
	//drawOrder Pointer to character body, arms and legs
	drawOrder* characterBody;
	drawOrder* characterLeftArm;
	drawOrder* characterRightArm;
	drawOrder* characterLeftLeg;
	drawOrder* characterRightLeg;
	//viariables to store distance moved
	float distanceMovedInOneDir;
	//viariables to store rotation of character body
	float charBodyAngleRotate;
	//viariables to store rotation of character arm
	float charArmRotate;
	//viariables to check whether the character left arm is rotating upward
	bool leftArmRotateUp;
	//Vector3 to store position checkpoint
	Vector3 points[10];
	//Walking state
	bool walking;
	//Time spent walking
	float timeWalking;
	//Idling state
	bool idling;
	//Time spent idling
	float timeIdling;
	//Default position
	Vector3 defaultPoint;
	float defaultCharBodyAngleRotate;
public:
	ShopperWandererLv2(void);
	~ShopperWandererLv2(void);
	
	void SetPosition(int No);
	void Update(const double dt);
	void Reset();
	void DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg);
	void RotateChar(ShopperWandererLv2& OtherShopper);
	Vector3 GetPos();
	bool IsBlocking(ShopperWandererLv2& OtherShopper, float toTurn);
};