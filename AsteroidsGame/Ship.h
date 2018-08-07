#pragma once
#include "stdafx.h"

class Ship {
	float speed;
	float shootCooldown; // Determines the cooldown between shots
	float lastTimeShoot; // Last time a bullet was shot
	bool canShoot(); // Returns true or false depending on whether a bullet can be spawned
public:
	Ship();
	Ship( float sSpeed);
	void drawSelf();
	float positionX, positionY;
	float w, h, d; // Width height and depth of the ship
	void move(float frameDelta);
	bool goRight;
	bool goLeft;
	bool shoot; // Indicates that spacebar has been pressed (the user wants to shoot)
	bool spawnBullet; // Indicates whether a bullet should be spawned next update
};