#include "stdafx.h"
#include "Game.h"
#include <iostream>
const GLfloat LIGHT_POS[] = { 0.0f, 10.0f, 10.0f, 0.0f };
const GLfloat LIGHT_DIFF[] = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat LIGHT_POS2[] = { 0.0f, -10.0f, 20.0f, 0.0f };
const GLfloat LIGHT_DIFF2[] = {0.3f, 0.3f, 0.3f, 1.0f };
const float ZNEAR = 0.1f;
const float ZFAR = 1000.0f;


bool Game::CheckPlayerCollision()
{
	for (unsigned int i = 0; i < asteroids.size(); i++) {
		// Is an asteroid at the same height as our player?
		if (asteroids[i].positionY <= player.positionY + player.h && !(asteroids[i].positionY + asteroids[i].h < player.positionY -player.h))  {
			// Is an asteroid at the same width as our player?
			if (asteroids[i].positionX + asteroids[i].w >= player.positionX -player.w && player.positionX + player.w >= asteroids[i].positionX - asteroids[i].h) {
				return true;
			}
		}
	}
	return false;
}

bool Game::CheckBulletCollision(Bullet bullet, int & numOfAsteroid)
{
	for (unsigned int i = 0; i < asteroids.size(); i++) {
		// Is an asteroid at the same height as the bullet?
		if (asteroids[i].positionY <= bullet.positionY + bullet.h && !(asteroids[i].positionY + asteroids[i].h < bullet.positionY - bullet.h)) {
			// Is an asteroid at the same width as the bullet?
			if (asteroids[i].positionX + asteroids[i].w >= bullet.positionX - bullet.w && bullet.positionX + bullet.w  >= asteroids[i].positionX - asteroids[i].w) {
				numOfAsteroid = i; // The asteroid which we collided with
				return true;
			}
		}
	}
	return false;
}

/* Loads the level, creates the player, clears asteroids and bullets vectors, spawns initial asteroids*/
void Game::LoadLevel()
{
	player = Ship();
	asteroids.clear();
	bullets.clear();
	asteroids.push_back(Asteroid());
	asteroids.push_back(Asteroid());
	asteroids.push_back(Asteroid());
}

/* Initializes srand(), last and current time and calls LoadLevel  */
Game::Game()
{
	srand(time(0));
	lastTime = 0;
	timeNow = 0;
	LoadLevel();
}



void Game::Start(int width, int height)
{
	glClearColor(0,0,0,0); // black
	glShadeModel(GL_FLAT);

	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFF);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POS);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, LIGHT_DIFF2);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_POS2);
	glEnable(GL_LIGHT1);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(45.0, width / height, ZNEAR, ZFAR);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void Game::Update()

{		// frameDelta is used to make Player, Bullet and Asteroid movement frame independent 
		timeNow = glfwGetTime();
		frameDelta = (timeNow - lastTime);
		lastTime = timeNow;

		//Process player
		glPushMatrix();
		player.move(frameDelta);
		player.drawSelf();
		glPopMatrix();

		// If the SpawnBullet flag is on, reset the flag and create a bullet at the player's position
		if (player.spawnBullet) {
			player.spawnBullet = false;
			bullets.push_back(Bullet(player.positionX,player.positionY));
		}
		//****************//

		//Process Bullets
		for (unsigned int i = 0; i < bullets.size(); i++) {

			glPushMatrix();
			// Check for collision between bullet and asteroids 
			if (CheckBulletCollision(bullets[i],asteroidCollided)) { 
				bullets.erase(bullets.begin() + i);
				asteroids.erase(asteroids.begin() + asteroidCollided);
				asteroids.push_back(Asteroid());// Shooting down an asteroid spawns 2 more
				asteroids.push_back(Asteroid()); 
			}
			else {
				bullets[i].move(frameDelta);
				bullets[i].drawSelf();

				// If a bullet is out of bounds, delete it
				if (bullets[i].outOfBounds)
					bullets.erase(bullets.begin() + i);

			}
			glPopMatrix();

		}
		//**************//

		//Process Asteroids
		for (unsigned int i = 0; i < asteroids.size(); i++) {
			glPushMatrix();

			asteroids[i].move(frameDelta);
			asteroids[i].drawSelf();

			// If an asteroid is out of bounds, delete it
			if (asteroids[i].outOfBounds) {
				asteroids.erase(asteroids.begin() + i);
				asteroids.push_back(Asteroid());
			}
			glPopMatrix();
		}
		/* Check for collision between the player and asteroids. If collided, restart the game*/
		if (CheckPlayerCollision()) {
			this->LoadLevel();
		}
		//****************//
		
}
