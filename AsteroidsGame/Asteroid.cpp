#include "stdafx.h"
#include "Asteroid.h"

Asteroid::Asteroid()
{
	speed = 0.5 +static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1-0.5))); // Randomize falling speed
	positionX = -3 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3 - (-3) ))); // Randomize spawn location
	xShift = -0.002 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.002 - (-0.002)))); // Randomize shift of x position
	sizeX = 0.6 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.4 - (0.6)))); // Add slight randomness to size width
	sizeY = 0.6 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.4 - (0.6)))); // Add slight randomness to size height
	rotationShift = -5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5 - (-5)))); // Randomize rotation

	movement[0] = xShift; // X
	movement[1] = speed; // Y
	movement[2] = 0.0; // Z

	positionY = 4; // Starting height (4 is offscreen because we don't want the asteroids to spawn on our eyes)
	rotationX = rotationY = 0; // Current rotation
	w=0.3*sizeX; // Width
	h=0.3*sizeY; // Height
	d = 0.5 ; // Depth
	outOfBounds = false; // Is the asteroid ready to be deleted?
}

void Asteroid::move(float frameDelta)
{
	if (positionY < -4 -h)
		outOfBounds = true;
	
	positionX += movement[0] * frameDelta;
	positionY -= movement[1] * frameDelta;
	rotationX += rotationShift * frameDelta;
}

void Asteroid::drawSelf()
{
	
	glTranslatef(positionX, positionY, -8);
	glRotatef(rotationX,1,1 , 0);

	// Front (camera sees as back)
	glBegin(GL_POLYGON);

	glColor3f(1.0, 1.0, 1.0);  //white
	glVertex3f(w, -h, -d);     
	glVertex3f(w, h, -d);      
	glVertex3f(-w, h, -d);      
	glVertex3f(-w, -h, -d);      
	glEnd();

	// Back (camera sees as front)
	glBegin(GL_POLYGON);

	glColor3f(1.0, 1.0, 1.0);//white
	glVertex3f(w, -h, d);
	glVertex3f(w, h, d);
	glVertex3f(-w, h, d);
	glVertex3f(-w, -h, d);
	glEnd();

	// Right
	glBegin(GL_POLYGON);

	glColor3f(0.7, 0.0, 0.0); //red
	glVertex3f(w, -h, -d);
	glVertex3f(w, h, -d);
	glVertex3f(w, h, d);
	glVertex3f(w, -h, d);
	glEnd();

	// Left
	glBegin(GL_POLYGON);

	glColor3f(0.7, 0.0, 0.0); //red
	glVertex3f(-w, -h, d);
	glVertex3f(-w, h, d);
	glVertex3f(-w, h, -d);
	glVertex3f(-w, -h, -d);
	glEnd();

	// Top
	glBegin(GL_POLYGON);

	glColor3f(0.7, 0.0, 0.0); // red
	glVertex3f(w, h, d);
	glVertex3f(w, h, -d);
	glVertex3f(-w, h, -d);
	glVertex3f(-w, h, d);
	glEnd();

	// Bottom
	glBegin(GL_POLYGON);

	glColor3f(0.7, 0.0, 0.0); // red
	glVertex3f(w, -h, -d);
	glVertex3f(w, -h, d);
	glVertex3f(-w, -h, d);
	glVertex3f(-w, -h, -d);
	glEnd();
}
