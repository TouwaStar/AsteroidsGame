#pragma once
#include "stdafx.h"

class Asteroid {

	float speed; // Randomly generated falling speed
	float rotationX, rotationY; // Determines the current rotation along the X and Y axis
	glm::vec3 movement; // Stores the downward movement along with the X Shift in a neat container, uses 0 for depth shift
	float xShift; // Determines the random shift on the X axis
	float sizeX,sizeY; // Determines the randomness factor of height and width
	float rotationShift; // Determines the random rotation shift
public:
	Asteroid();
	float positionX, positionY; // Current position along the X and Y axis. Initial X position is randomly generated
	float w, h, d; // Width, Depth and Height of asteroid
	void move(float frameDelta);
	void drawSelf();
	bool outOfBounds; // Determines whether the asteroid is out of visible game area and should be removed;
	
};