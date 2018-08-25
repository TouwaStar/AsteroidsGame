#pragma once
#include "stdafx.h"
#include "GameObject.h"
class Asteroid : public GameObject
{
	float rotationX, rotationY; // Determines the current rotation along the X and Y axis
	glm::vec3 movement; // Stores the downward movement along with the X Shift in a neat container, uses 0 for depth shift
	float xShift; // Determines the random shift on the X axis
	float sizeX,sizeY; // Determines the randomness factor of height and width
	float rotationShift; // Determines the random rotation shift
public:
	Asteroid();
	void move(float frameDelta);
	void drawSelf() const;
	
};