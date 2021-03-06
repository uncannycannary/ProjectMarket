/****************************************************************************/
/*!
\file DoorInteraction.cpp
\author Tan Jie Rong
\par email: soupsf@hotmail.com
\brief
functions for door interactions
*/
/****************************************************************************/
#include "DoorInteraction.h"
/****************************************************************************/
/*!
\brief
default constructor that defines ranges and speed
*/
/****************************************************************************/
DoorInteraction::DoorInteraction(void)
{
	// Ranges set for bool update in main
	TravelatorIsInrange = false;
	LiftDoorInRange = false;
	//door speed
	DoorSlidingSpeed = 9;
}
/****************************************************************************/
/*!
\brief
default destructor 
*/
/****************************************************************************/
DoorInteraction::~DoorInteraction(void)
{
}
/****************************************************************************/
/*!
\brief
to take in door parts obj from main
\param darwOrder& (door parts)
		to pass in draworder
*/
/****************************************************************************/
void DoorInteraction::DrawIsEqualTo(drawOrder& TempOuterDoor1Left, drawOrder& TempOuterDoor1Right, drawOrder& TempOuterDoor2Left, drawOrder& TempOuterDoor2Right, drawOrder& TempInnerDoor1, drawOrder& TempInnerDoor2, drawOrder& TempLiftDoor1Left, drawOrder& TempLiftDoor1Right, drawOrder& TempLiftDoor2Left, drawOrder& TempLiftDoor2Right)
{
	//passing in of drawOrder
	OuterDoor1Left = &TempOuterDoor1Left;
	OuterDoor1Right = &TempOuterDoor1Right;
	OuterDoor2Left = &TempOuterDoor2Left;
	OuterDoor2Right = &TempOuterDoor2Right;
	InnerDoor1 = &TempInnerDoor1;
	InnerDoor2 = &TempInnerDoor2;
	LiftDoor1Left = &TempLiftDoor1Left;
	LiftDoor1Right = &TempLiftDoor1Right;
	LiftDoor2Left = &TempLiftDoor2Left;
	LiftDoor2Right = &TempLiftDoor2Right;
}
/****************************************************************************/
/*!
\brief
to interact with door: in range, opening closing.
\param dt, Vector3& PlayerPos, const Vector3& ShopperPos
		dt for intake of moving according to time, Pos to get position of player and shopper
/****************************************************************************/
void DoorInteraction::InteractWithDoors(const double dt, const Vector3& PlayerPos, const Vector3& ShopperPos)
{
	//OuterDoor1
	Range<int> OuterDoor1RangeX(-7,7);
	Range<int> OuterDoor1RangeY(0,5);
	Range<int> OuterDoor1RangeZ(-18,1.732);

	if( (OuterDoor1RangeX.IsInRange(PlayerPos.x) && OuterDoor1RangeY.IsInRange(PlayerPos.y) && OuterDoor1RangeZ.IsInRange(PlayerPos.z) ) || (OuterDoor1RangeX.IsInRange(ShopperPos.x) && OuterDoor1RangeY.IsInRange(ShopperPos.y) && OuterDoor1RangeZ.IsInRange(ShopperPos.z)) )
	{
		if(OuterDoor1Left->transform.translate.x >= -6)
		{
			OuterDoor1Left-> transform.translate.x += -DoorSlidingSpeed * dt;
			OuterDoor1Right-> transform.translate.x += DoorSlidingSpeed * dt;
		}
	}

	else
	{
		if(OuterDoor1Left->transform.translate.x < -2)
		{
			OuterDoor1Left-> transform.translate.x += DoorSlidingSpeed * dt;
			OuterDoor1Right-> transform.translate.x += -DoorSlidingSpeed * dt;
		}
	}

	//InnderDoor 1 & 2
	Range<int> InnerDoorRangeX(-18,-13);
	Range<int> InnerDoor1RangeY(0,5);
	Range<int> InnerDoor2RangeY(10,15);
	Range<int> InnerDoorRangeZ(-28,-10);

	if((InnerDoorRangeX.IsInRange(PlayerPos.x) && InnerDoor1RangeY.IsInRange(PlayerPos.y) && InnerDoorRangeZ.IsInRange(PlayerPos.z)) || (InnerDoorRangeX.IsInRange(ShopperPos.x) && InnerDoor1RangeY.IsInRange(ShopperPos.y) && InnerDoorRangeZ.IsInRange(ShopperPos.z)))
	{
		if(InnerDoor1->transform.translate.x <= -12.5)
		{
			InnerDoor1-> transform.translate.x += DoorSlidingSpeed * dt;
		}
	}
	else
	{
		if(InnerDoor1 -> transform.translate.x > -17.5)
		{
			InnerDoor1-> transform.translate.x += -DoorSlidingSpeed * dt;
		}
	}

	if(InnerDoorRangeX.IsInRange(PlayerPos.x) && InnerDoor2RangeY.IsInRange(PlayerPos.y) && InnerDoorRangeZ.IsInRange(PlayerPos.z))
	{
		if(InnerDoor2->transform.translate.x <= -12.5)
		{
			InnerDoor2-> transform.translate.x += DoorSlidingSpeed * dt;
		}
	}
	else
	{
		if(InnerDoor2-> transform.translate.x > -17.5)
		{
			InnerDoor2-> transform.translate.x += -DoorSlidingSpeed * dt;
		}
	}

	//OuterDoor2
	Range<int> OuterDoor2RangeX(-14,-6);
	Range<int> OuterDoor2RangeY(0,5);
	Range<int> OuterDoor2RangeZ(-116,-93.7);

	if((OuterDoor2RangeX.IsInRange(PlayerPos.x) && OuterDoor2RangeY.IsInRange(PlayerPos.y) && OuterDoor2RangeZ.IsInRange(PlayerPos.z)) || (OuterDoor2RangeX.IsInRange(ShopperPos.x) && OuterDoor2RangeY.IsInRange(ShopperPos.y) && OuterDoor2RangeZ.IsInRange(ShopperPos.z)) )
	{
		if(OuterDoor2Left->transform.translate.x >= -17.2)
		{
			OuterDoor2Left-> transform.translate.x += -DoorSlidingSpeed * dt;
			OuterDoor2Right-> transform.translate.x += DoorSlidingSpeed * dt;
		}
	}

	else
	{
		if(OuterDoor2Left->transform.translate.x < -13)
		{
			OuterDoor2Left-> transform.translate.x += DoorSlidingSpeed * dt;
			OuterDoor2Right-> transform.translate.x += -DoorSlidingSpeed * dt;
		}
	}
}
/****************************************************************************/
/*!
\brief
function for door to open
\param dt, PlayerPos, bool OpenLiftDoorInput
		dt to slide door, PlayerPos to check if player is in range. bool to take in input in door is supposed to open
*/
/****************************************************************************/
void DoorInteraction::InteractWithLiftsOPEN(const double dt, Vector3& PlayerPos, bool OpenLiftDoorInput)	
{
	Range<int> LiftDoor1and2RangeX(13,18);
	Range<int> LiftDoor1RangeY(0,5);
	Range<int> LiftDoor2RangeY(10,15);
	Range<int> LiftDoor1and2RangeZ(-104,-83);

	if(OpenLiftDoorInput == true)
	{
		if(LiftDoor1and2RangeX.IsInRange(PlayerPos.x) && LiftDoor1RangeY.IsInRange(PlayerPos.y) && LiftDoor1and2RangeZ.IsInRange(PlayerPos.z))
		{		
			LiftDoorInRange = true;
			if(LiftDoor1Left->transform.translate.x >= 11.2)
			{
				LiftDoor1Left-> transform.translate.x += -2.5 * dt;
				LiftDoor1Right-> transform.translate.x += 2.5 * dt;
			}
		}

		else if(LiftDoor1and2RangeX.IsInRange(PlayerPos.x) && LiftDoor2RangeY.IsInRange(PlayerPos.y) && LiftDoor1and2RangeZ.IsInRange(PlayerPos.z))
		{
			LiftDoorInRange = true;
			if(LiftDoor2Left->transform.translate.x >= 11.2)
			{
				LiftDoor2Left-> transform.translate.x += -2.5 * dt;
				LiftDoor2Right-> transform.translate.x += 2.5 * dt;
			}
		}
		else 
		{
			LiftDoorInRange = false;
			//OpenLiftDoorInput = false;
		}
	}
}
/****************************************************************************/
/*!
\brief
function for door to close
\param dt, PlayerPos, bool OpenLiftDoorInput
		dt to slide door, PlayerPos to check if player is in range. bool to take in input in door is supposed to close
*/
/****************************************************************************/
void DoorInteraction::InteractWithLiftsCLOSE(const double dt, Vector3& PlayerPos, bool OpenLiftDoorInput)	
{
	Range<int> LiftDoor1and2RangeX(13,18);
	Range<int> LiftDoor1RangeY(0,5);
	Range<int> LiftDoor2RangeY(10,15);
	Range<int> LiftDoor1and2RangeZ(-104,-83);

	if(OpenLiftDoorInput == false)
	{
		if(LiftDoor1and2RangeX.IsInRange(PlayerPos.x) && LiftDoor1RangeY.IsInRange(PlayerPos.y) && LiftDoor1and2RangeZ.IsInRange(PlayerPos.z))
		{
			LiftDoorInRange = true;
			if(LiftDoor1Left->transform.translate.x < 14)
			{
				LiftDoor1Left-> transform.translate.x += 2.5 * dt;
				LiftDoor1Right-> transform.translate.x += -2.5 * dt;
			}
		}
		else if(LiftDoor1and2RangeX.IsInRange(PlayerPos.x) && LiftDoor2RangeY.IsInRange(PlayerPos.y) && LiftDoor1and2RangeZ.IsInRange(PlayerPos.z))
		{
			LiftDoorInRange = true;
			if(LiftDoor2Left->transform.translate.x < 14)
			{
				LiftDoor2Left-> transform.translate.x += 2.5 * dt;
				LiftDoor2Right-> transform.translate.x += -2.5 * dt;
			}
		}
		else
		{
			LiftDoorInRange = false;
		}

		if(LiftDoorInRange == false)
		{
			if(LiftDoor1Left->transform.translate.x < 14)
			{
				LiftDoor1Left-> transform.translate.x += 2.5 * dt;
				LiftDoor1Right-> transform.translate.x += -2.5 * dt;
			}
				if(LiftDoor2Left->transform.translate.x < 14)
			{
				LiftDoor2Left-> transform.translate.x += 2.5 * dt;
				LiftDoor2Right-> transform.translate.x += -2.5 * dt;
			}
		}
	}
}
/****************************************************************************/
/*!
\brief
function for player and trolley to teleport with lift
\param dt
		dt to slide door
\param PlayerPos
		PlayerPos to check if they are in range of lift. 
\param TrolleyPos
		TrolleyPos to check if they are in range of lift. 
\param bool isTakingTrolley
		bool to check if trolley is being held by player or not
*/
/****************************************************************************/
void DoorInteraction::TeleportWithLifts(const double dt, Vector3& PlayerPos, Vector3& TrolleyPos, bool isTakingTrolley)	
{
	//Lift > Lift translation
	Range<int> Lift0and1RangeX(12,19);
	Range<int> Lift0RangeY(0,5);
	Range<int> Lift1RangeY(10,15);
	Range<int> Lift0and1RangeZ(-101,-92);

	if(Lift0and1RangeX.IsInRange(PlayerPos.x) && Lift0RangeY.IsInRange(PlayerPos.y) && Lift0and1RangeZ.IsInRange(PlayerPos.z))
	{
		PlayerPos.y += 10;

		if(Lift0and1RangeX.IsInRange(TrolleyPos.x) && Lift0RangeY.IsInRange(TrolleyPos.y) && Lift0and1RangeZ.IsInRange(TrolleyPos.z))
		{

			if (isTakingTrolley == false)
			{
				TrolleyPos.y += 10;
			}

			else if (isTakingTrolley == true)
			{
				TrolleyPos.y = 14;
			}
		}
	}	

	else if(Lift0and1RangeX.IsInRange(PlayerPos.x) && Lift1RangeY.IsInRange(PlayerPos.y) && Lift0and1RangeZ.IsInRange(PlayerPos.z))
	{
		PlayerPos.y -= 10;

		if(Lift0and1RangeX.IsInRange(TrolleyPos.x) && Lift1RangeY.IsInRange(TrolleyPos.y) && Lift0and1RangeZ.IsInRange(TrolleyPos.z))
		{

			if (isTakingTrolley == false)
			{
				TrolleyPos.y -= 10;
			}

			else if (isTakingTrolley == true)
			{
				TrolleyPos.y = 4;
			}
		}
	}	
}
/****************************************************************************/
/*!
\brief
function for trolley to teleport in case player went other levels
\param dt
		dt to slide door
\param PlayerPos
		PlayerPos to check if they are in range of lift. 
\param TrolleyPos
		TrolleyPos to check if they are in range of lift. 
*/
/****************************************************************************/
void DoorInteraction::TrolleyTeleportWithoutPlayer(const double dt, Vector3& PlayerPos, Vector3& TrolleyPos)	
{
	Range<int> Lift0and1RangeX(12,19);
	Range<int> Lift0RangeY(0,5);
	Range<int> Lift1RangeY(10,15);
	Range<int> Lift0and1RangeZ(-101,-92);

	if (Lift0and1RangeX.IsInRange(TrolleyPos.x) && (Lift0RangeY.IsInRange(TrolleyPos.y) || Lift1RangeY.IsInRange(TrolleyPos.y)) && Lift0and1RangeZ.IsInRange(TrolleyPos.z))
	{
		if (TrolleyPos.y < 6 && PlayerPos.y > 6)
		{
			TrolleyPos.y += 10;
		}

		else if (TrolleyPos.y > 6 && PlayerPos.y < 6)
		{
			TrolleyPos.y -= 10;
		}
	}
}
/****************************************************************************/
/*!
\brief
function for player to travel on travelator
\param dt
		dt to update player translation
\param PlayerPos
		PlayerPos to check if they are in range with travelator
*/
/****************************************************************************/
void DoorInteraction::InteractWithTravelator(const double dt, Vector3& PlayerPos)	
{
	Range<int> TravelatorRangeX(-14,10.716);
	Range<int> TravelatorRangeY(3,16);
	Range<int> TravelatorLeftUpRangeZ(-21.638,-20.788);
	Range<int> TravelatorRightDownRangeZ(-24.337,-23.234);

	if(TravelatorRangeX.IsInRange(PlayerPos.x) && TravelatorRangeY.IsInRange(PlayerPos.y) && TravelatorRightDownRangeZ.IsInRange(PlayerPos.z))
	{
		TravelatorIsInrange = true;
		PlayerPos.x += 6 * dt;
		PlayerPos.y += -2.4 * dt;
	}


	else if(TravelatorRangeX.IsInRange(PlayerPos.x) && TravelatorRangeY.IsInRange(PlayerPos.y) && TravelatorLeftUpRangeZ.IsInRange(PlayerPos.z))
	{
		TravelatorIsInrange = true;
		PlayerPos.x += -6 * dt;
		PlayerPos.y += 2.4 * dt;
	}

	else
	{
		TravelatorIsInrange = false;
	}
}
/****************************************************************************/
/*!
\brief
Return if player in range to travelator
\return
		is in range
*/
/****************************************************************************/
bool DoorInteraction::GetTravelatorInRange(void)
{
	return TravelatorIsInrange;
}
/****************************************************************************/
/*!
\brief
Return if player in range to lift door
\return
		is in range
*/
/****************************************************************************/
bool DoorInteraction::GetLiftDoorInRange(void)
{
	return LiftDoorInRange;
}