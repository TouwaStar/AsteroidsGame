#pragma once
#include "stdafx.h"
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet(float x, float y); // X and Y are coordinates used to determine from where will the bullet spawn
	void drawSelf() const;
	void move(float frameDelta);
};