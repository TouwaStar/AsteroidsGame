#pragma once
#include "stdafx.h"
#include "GameObject.h"
class Ship : public GameObject 
{
private:
	float shootCooldown; // Determines the cooldown between shots
	float lastTimeShot; // Last time a bullet was shot
public:
	Ship();
	Ship( float sSpeed);
	void drawSelf() const;
	void move(float frameDelta);
	bool goRight;
	bool goLeft;
	bool shoot; // Indicates that spacebar has been pressed (the user wants to shoot)
	bool spawnBullet; // Indicates whether a bullet should be spawned next update
};