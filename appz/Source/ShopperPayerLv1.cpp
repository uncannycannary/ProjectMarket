#include "ShopperPayerLv1.h"


ShopperPayerLv1::ShopperPayerLv1(void)
{
	distanceMovedInOneDir = 0;
	charBodyAngleRotate = 0;
	charArmRotate = 30;
	leftArmRotateUp = true;
	points[0] = Vector3(-17.5,5,-10);// Behind inner entrance door, inside entrance room
	points[1] = Vector3(-17.5,5,-51);// Position to rotate toward the two cabinets
	points[2] = Vector3(-7.5,5,-51);// Between two cabinets
	points[3] = Vector3(-17.5,5,-83);// Beside cashier table at side
	points[4] = Vector3(-17.5,5,-95);// Position to rotate around the cashier table
	points[5] = Vector3(-11.5,5,-95);// Position to rotate toward exit door
	points[6] = Vector3(-11.5,5,-110);// Behind outer exit door, outside
	idling = false;
	walking = true;
	timeIdling = 0;
	timeWalking = 0;
}


ShopperPayerLv1::~ShopperPayerLv1(void)
{
}

void ShopperPayerLv1::Init()
{
}

void ShopperPayerLv1::Render()
{
}

void ShopperPayerLv1::SetPosition(int No)
{
	characterBody->transform.translate = points[No];
	if(No == 2 || No == 4)
		characterBody->transform.rotate.y = 90;
	else
		characterBody->transform.rotate.y = 180;
	defaultPoint = points[No];
	defaultCharBodyAngleRotate = characterBody->transform.rotate.y;
}

void ShopperPayerLv1::Update(const double dt)
{
	//if(idling == true)
	//{
	//	characterLeftArm->selfTransform.rotate.x = -5;
	//	characterRightArm->selfTransform.rotate.x = -5;
	//	charArmRotate = 30;
	//	characterLeftLeg->selfTransform.rotate.x = 0;
	//	characterRightLeg->selfTransform.rotate.x = 0;
	//	timeIdling += dt;
	//	if(timeIdling > 5)
	//	{
	//		timeIdling = 0;
	//		idling = false;
	//		walking = true;
	//	}
	//}
	//else
	//{
	//	//If distance less than 15, character walking
	//	if(distanceMovedInOneDir < 15)
	//	{
	//		characterBody->transform.translate += characterBody->transform.rotate.MatrixY() * Vector3(0, 0, dt * 2);
	//		distanceMovedInOneDir += dt * 2;
	//		if(charArmRotate > 60)
	//			leftArmRotateUp = false;
	//		else if(charArmRotate < 0)
	//			leftArmRotateUp = true;
	//		if(leftArmRotateUp == true)
	//		{
	//			characterLeftArm->selfTransform.rotate.x -= dt * 80;
	//			characterRightArm->selfTransform.rotate.x += dt * 80;
	//			charArmRotate += dt * 80;
	//			characterLeftLeg->selfTransform.rotate.x += dt * 40;
	//			characterRightLeg->selfTransform.rotate.x -= dt * 40;
	//		}
	//		else
	//		{
	//			characterLeftArm->selfTransform.rotate.x += dt * 80;
	//			characterRightArm->selfTransform.rotate.x -= dt * 80;
	//			charArmRotate -= dt * 80;
	//			characterLeftLeg->selfTransform.rotate.x -= dt * 40;
	//			characterRightLeg->selfTransform.rotate.x += dt * 40;
	//		}
	//	}
	//	timeWalking += dt;
	//	if(timeWalking > 10)
	//	{
	//		timeWalking = 0;
	//		if(rand() % 2 == 0)
	//		{
	//			idling = false;
	//			walking = true;
	//		}
	//		else
	//		{
	//			idling = true;
	//			walking = false;
	//		}
	//	}
	//}
}

void ShopperPayerLv1::Exit()
{
}

void ShopperPayerLv1::Reset()
{
	characterBody->transform.translate = defaultPoint;
	characterBody->transform.rotate.y = defaultCharBodyAngleRotate;
	idling = false;
	walking = true;
	timeIdling = 0;
	timeWalking = 0;
	distanceMovedInOneDir = 0;
	charBodyAngleRotate = 0;
	characterLeftArm->selfTransform.rotate.x = -5;
	characterRightArm->selfTransform.rotate.x = -5;
	charArmRotate = 30;
	characterLeftLeg->selfTransform.rotate.x = 0;
	characterRightLeg->selfTransform.rotate.x = 0;
	leftArmRotateUp = true;
}

void ShopperPayerLv1::DrawIsEqualTo(drawOrder& TempCharacterBody, drawOrder& TempCharacterLeftArm, drawOrder& TempCharacterRightArm, drawOrder& TempCharacterLeftLeg, drawOrder& TempCharacterRightLeg)
{
	characterBody = &TempCharacterBody;
	characterLeftArm = &TempCharacterLeftArm;
	characterRightArm = &TempCharacterRightArm;
	characterLeftLeg = &TempCharacterLeftLeg;
	characterRightLeg  = &TempCharacterRightLeg;
}

void ShopperPayerLv1::RotateChar(ShopperPayerLv1& OtherShopper)
{
//	//If distance more than 15, character rotate
//	if(distanceMovedInOneDir > 15)
//	{
//		if(characterBody->transform.translate.x <= points[0].x + 1)// Left side points
//		{
//			if(characterBody->transform.translate.z >= points[0].z - 1)// front point
//			{
//				int temp = rand() % 2;
//				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 180; // toward -z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,90) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 90; // toward +x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//			else if(characterBody->transform.translate.z <= points[9].z + 1)// back point
//			{
//				int temp = rand() % 2;
//				if(temp == 0 && IsBlocking(OtherShopper,0) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 0; // toward +z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,90) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 90; // toward +x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//			else// middle points
//			{
//				int temp = rand() % 3;
//				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 180; // toward -z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,0) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 0; // toward +z
//				}
//				else if(temp == 2 && IsBlocking(OtherShopper,90) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 90; // toward +x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//		}
//		else
//		{
//			if(characterBody->transform.translate.z >= points[0].z - 1)// front point
//			{
//				int temp = rand() % 2;
//				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 180; // toward -z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,270) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 270; // toward -x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//			else if(characterBody->transform.translate.z <= points[9].z + 1)// back point
//			{
//				int temp = rand() % 2;
//				if(temp == 0 && IsBlocking(OtherShopper,0) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 0; // toward +z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,270) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 270; // toward -x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//			else// middle points
//			{
//				int temp = rand() % 3;
//				if(temp == 0 && IsBlocking(OtherShopper,180) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 180; // toward -z
//				}
//				else if(temp == 1 && IsBlocking(OtherShopper,0) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 0; // toward +z
//				}
//				else if(temp == 2 && IsBlocking(OtherShopper,270) == false)
//				{
//					//reset disance moved in one direction
//					distanceMovedInOneDir = 0;
//					charBodyAngleRotate = 270; // toward -x
//				}
//				else
//				{
//					idling = true;
//					walking = false;
//					timeWalking = 0;
//				}
//			}
//		}
//		//rotate body
//		characterBody->transform.rotate.y = charBodyAngleRotate;
//	}
}

Vector3 ShopperPayerLv1::GetPos()
{
	return characterBody->transform.translate;
}

bool ShopperPayerLv1::IsBlocking(ShopperPayerLv1& OtherShopper, float toTurn)
{/*
	Vector3 target = characterBody->transform.translate;
	if(toTurn == 0)
		target += Vector3(0, 0, 15);
	else if(toTurn == 90)
		target += Vector3(15, 0, 0);
	else if(toTurn == 180)
		target += Vector3(0, 0, -15);
	else
		target += Vector3(-15, 0, 0);
	if(target.x < OtherShopper.GetPos().x + 15 && target.x > OtherShopper.GetPos().x - 15 && target.y == OtherShopper.GetPos().y && target.z < OtherShopper.GetPos().z + 15 && target.z > OtherShopper.GetPos().z - 15)
		return true;
	else*/
		return false;
}