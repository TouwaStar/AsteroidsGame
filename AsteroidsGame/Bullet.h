#pragma once
#include "stdafx.h"

class Bullet {
	float speed; // Bullets speed
public:
	Bullet(float x, float y); // X and Y are coordinates used to determine from where will the bullet spawn
	float positionX, positionY; // Keep track of bullets position
	float w, h, d; // Width height and depth used when creating bullets mesh
	void drawSelf();
	void move(float frameDelta);
	bool outOfBounds; // Indicates whether the bullet is out of visible game screen and should be cleaned up
};