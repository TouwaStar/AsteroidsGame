#include "stdafx.h"
#include "Ship.h"

bool Ship::canShoot()
{
	if (glfwGetTime() - lastTimeShoot > shootCooldown) {
		lastTimeShoot = glfwGetTime();
		return true;
	}
	return false;
}

Ship::Ship()
{
	goRight = goLeft = shoot = false;
	positionX = 0; // Current position along the X Axis
	positionY = -2.5f;// Current position along the Y Axis. -2.5 because we want the ship to be constantly situated at the bottom of the screen
	speed = 5; // Ship speed
	w = 0.2; // Width
	h = 0.1; // Height
	d = 0.2; // Depth
	shootCooldown = 0.5f;
	lastTimeShoot = -5.0;
	spawnBullet = false; // Should a bullet be spawned in the next update

}

Ship::Ship(float sSpeed)
{
	goRight = goLeft = shoot = false;
	positionX = 0;  // Current position along the X Axis
	positionY = -2.5f; // Current position along the Y Axis. -2.5 because we want the ship to be constantly situated at the bottom of the screen
	speed = sSpeed; // Ship speed
	w = 0.2; // Width
	h = 0.1; // Height
	d = 0.2; // Depth
	shootCooldown = 0.5f;
	lastTimeShoot = -5.0;
	spawnBullet = false; // Should a bullet be spawned in the next update
		
}

void Ship::drawSelf()
{
	glTranslatef(positionX, positionY, -8);

	// Front (camera sees as back)
	glBegin(GL_POLYGON);

	glColor3f(0, 0.5, 0.5);  // Teal ?
	glVertex3f(w, -h, -d);      
	glVertex3f(w, h, -d);      
	glVertex3f(-w, h, -d);      
	glVertex3f(-w, -h, -d);      
	glEnd();

	// Back (camera sees as front)
	glBegin(GL_POLYGON);

	glColor3f(1.0, 1.0, 0.0); // yellow
	glVertex3f(w, -h, d);
	glVertex3f(w, h, d);
	glVertex3f(-w, h, d);
	glVertex3f(-w, -h, d);
	glEnd();

	// Right
	glBegin(GL_POLYGON);

	glColor3f(0, 0.5, 0.5);  // Teal ?
	glVertex3f(w, -h, -d);
	glVertex3f(w, h, -d);
	glVertex3f(w, h, d);
	glVertex3f(w, -h, d);
	glEnd();

	// Left
	glBegin(GL_POLYGON);

	glColor3f(0, 0.5, 0.5);  // Teal ?
	glVertex3f(-w, -h, d);
	glVertex3f(-w, h, d);
	glVertex3f(-w, h, -d);
	glVertex3f(-w, -h, -d);
	glEnd();

	// Top
	glBegin(GL_POLYGON);

	glColor3f(0, 0.7, 0);  //  Green
	glVertex3f(w, h, d);
	glVertex3f(w, h, -d);
	glVertex3f(-w, h, -d);
	glVertex3f(-w, h, d);
	glEnd();

	// Bottom
	glBegin(GL_POLYGON);

	glColor3f(0, 0.5, 0.5);  // Teal ?
	glVertex3f(w, -h, -d);
	glVertex3f(w, -h, d);
	glVertex3f(-w, -h, d);
	glVertex3f(-w, -h, -d);
	glEnd();
	
}




void Ship::move(float frameDelta)
{
	if (goLeft && positionX > -3) 
		positionX -= speed*frameDelta;
	if (goRight && positionX <3) 
		positionX += speed*frameDelta;
	if (shoot && canShoot()) 
		spawnBullet = true;
}
