#pragma once

#include "character.h"
#include "Camera.h"

class Player :
	public Character
{
public:
	Player(void);
	~Player(void);
	
	virtual void Init() = 0;
	virtual Vector3 Update(Camera camera) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	
	//movement
	virtual Vector3 MoveForward(Camera camera, double movingSpeed) = 0;
	virtual Vector3 MoveBackward(Camera camera, double movingSpeed) = 0;
	virtual Vector3 MoveRight(Camera camera, double movingSpeed) = 0;
	virtual Vector3 MoveLeft(Camera camera, double movingSpeed) = 0;
};

