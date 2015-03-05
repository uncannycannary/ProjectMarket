#pragma once

#include "player.h"
#include "Range.h"

class PlayerHuman :
	public Player
{
public:
	PlayerHuman(void);
	~PlayerHuman(void);
	
	Vector3 Update(Camera camera);
	void takeItems();
	void returnItems();
	
	//movement
	Vector3 MoveForward(Camera camera, double movingSpeed);
	Vector3 MoveBackward(Camera camera, double movingSpeed);
	Vector3 MoveRight(Camera camera, double movingSpeed);
	Vector3 MoveLeft(Camera camera, double movingSpeed);
	void TakingTrolley(const Camera& camera);
	void ReleaseTrolley(const Vector3& TrolleyCurrentPos);
};

