#pragma once
#include "stdafx.h"
class GameObject 
{
protected:
	float speed; // Objects speed
public:
	float positionX, positionY; // Keep track of objects position
	float w, h, d; // Width height and depth of the object
	virtual void drawSelf() const {};
	virtual void move(float frameDelta) {};
	bool outOfBounds; // Indicates whether the object is out of bounds
}; 
