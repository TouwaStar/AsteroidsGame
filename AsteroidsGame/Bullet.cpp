#include "stdafx.h"
#include "Bullet.h"
Bullet::Bullet(float x, float y)
{
	positionX = x;
	positionY = y;
	speed = 2;
	w = 0.05;
	h = 0.1;
	d = 0.1;
	outOfBounds = false;
}

void Bullet::drawSelf() const
{

	glTranslatef(positionX, positionY, -8);

	// Front (camera sees as back)
	glBegin(GL_POLYGON);

	glColor3f(1.0, 1.0, 1.0); // white
	glVertex3f(w, -h, -d);      
	glVertex3f(w, h, -d);      
	glVertex3f(-w, h, -d);     
	glVertex3f(-w, -h, -d);     
	glEnd();

	// Back (camera seees as front)
	glBegin(GL_POLYGON);

	glColor3f(0.0, 0.7, 0.0); // green
	glVertex3f(w, -h, d);
	glVertex3f(w, h, d);
	glVertex3f(-w, h, d);
	glVertex3f(-w, -h, d);
	glEnd();

	// Right
	glBegin(GL_POLYGON);

	glColor3f(1.0, 1.0, 1.0); // white
	glVertex3f(w, -h, -d);
	glVertex3f(w, h, -d);
	glVertex3f(w, h, d);
	glVertex3f(w, -h, d);
	glEnd();

	// Left
	glBegin(GL_POLYGON);

	glColor3f(1.0, 1.0, 1.0); // white
	glVertex3f(-w, -h, d);
	glVertex3f(-w, h, d);
	glVertex3f(-w, h, -d);
	glVertex3f(-w, -h, -d);
	glEnd();

	// Top
	glBegin(GL_POLYGON);

	glColor3f(1.0, 1.0, 1.0); // white
	glVertex3f(w, h, d);
	glVertex3f(w, h, -d);
	glVertex3f(-w, h, -d);
	glVertex3f(-w, h, d);
	glEnd();

	// Bottom
	glBegin(GL_POLYGON);

	glColor3f(1.0, 1.0, 1.0); // white
	glVertex3f(w, -h, -d);
	glVertex3f(w, -h, d);
	glVertex3f(-w, -h, d);
	glVertex3f(-w, -h, -d);
	glEnd();
}

void Bullet::move(float frameDelta)
{
	positionY += speed * frameDelta;

	if (positionY >= 4)
		outOfBounds = true;
}
