#include "stdafx.h"
#include "Game.h"
#include <iostream>
const GLfloat LIGHT_POS[] = { 0.0f, 10.0f, 10.0f, 0.0f };
const GLfloat LIGHT_DIFF[] = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat LIGHT_POS2[] = { 0.0f, -10.0f, 20.0f, 0.0f };
const GLfloat LIGHT_DIFF2[] = {0.3f, 0.3f, 0.3f, 1.0f };
const float ZNEAR = 0.1f;
const float ZFAR = 1000.0f;

bool Game::checkCollision(const GameObject& object)
{
	for (unsigned int i = 0; i < asteroids.size(); i++) {
		// Is an asteroid at the same height as our object?
		if (asteroids[i].positionY <= object.positionY + object.h && !(asteroids[i].positionY + asteroids[i].h < object.positionY - object.h))  {
			// Is an asteroid at the same width as our player?
			if (asteroids[i].positionX + asteroids[i].w >= object.positionX - object.w && object.positionX + object.w >= asteroids[i].positionX - asteroids[i].w) {
				asteroidCollided = i;
				return true;
			}
		}
	}
	return false;
}

/* Loads the level, creates the player, clears asteroids and bullets vectors, spawns initial asteroids*/
void Game::loadLevel()
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
	loadLevel();
}

void Game::start(int width, int height) const
{
	//Setup and enable specific openGL modes
	glClearColor(0,0,0,0); // black
	glShadeModel(GL_FLAT);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//Set Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFF);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POS);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LIGHT_DIFF2);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_POS2);
	glEnable(GL_LIGHT1);
	//Prepare matrices
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, width / height, ZNEAR, ZFAR);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Game::update()
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
		//Process Bullets
		for (unsigned int i = 0; i < bullets.size();) {
			glPushMatrix();
			// Check for collision between bullet and asteroids 
			if (checkCollision(bullets[i])) { 
				bullets.erase(bullets.begin() + i);
				asteroids.erase(asteroids.begin() + asteroidCollided);
				asteroids.push_back(Asteroid());// Shooting down an asteroid spawns 2 more
				asteroids.push_back(Asteroid()); 
			}else {
				bullets[i].move(frameDelta);
				bullets[i].drawSelf();
				// If a bullet is out of bounds, delete it
				if (bullets[i].outOfBounds) {
					bullets.erase(bullets.begin() + i);
				}else {
					i++; // Incrementing the iterator here prevents skipping processing of an elements in case there is a deletion
				}
			}
			glPopMatrix();
		}
		//Process Asteroids
		for (unsigned int i = 0; i < asteroids.size();) {
			glPushMatrix();

			asteroids[i].move(frameDelta);
			asteroids[i].drawSelf();

			// If an asteroid is out of bounds, delete it
			if (asteroids[i].outOfBounds) {
				asteroids.erase(asteroids.begin() + i);
				asteroids.push_back(Asteroid());
			}else {
				i++; // Incrementing the iterator here prevents skipping processing of an elements in case there is a deletion
			}
			glPopMatrix();
		}
		// Check for collision between the player and asteroids. If collided, restart the game
		if (checkCollision(player)) {
			this->loadLevel();
		}
}
