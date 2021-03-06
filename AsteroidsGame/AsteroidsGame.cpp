#include "stdafx.h"
#include "Game.h"
#include <iostream>
const int WIN_WIDTH = 1440;
const int WIN_HEIGHT = 900;
Game game = Game();

// Switches player movement flags depending on the keyboard input.
void callback(GLFWwindow* win, int key, int code, int action, int mod) {
	
	// We want to take action if a key was pressed or if it was released
	if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		bool pressed;

		if (action == GLFW_PRESS) {
			pressed = true; // If key was pressed we will switch a flag to true
		}
		else {
			pressed = false; // If it was released we will switch a flag to false
		}

		switch (key) {
		case GLFW_KEY_LEFT:
			game.player.goLeft = pressed;
			break;
		case GLFW_KEY_RIGHT:
			game.player.goRight = pressed;
			break;
		}

		if (key == GLFW_KEY_SPACE)
			game.player.shoot = pressed;
	}
}

void errorCallback(int error, const char* description)  {
	std::cerr << description << std::endl;
}

/* Initialize window, glfw, key callback etc. Then until the window needs to be closed
calls the Games Update() in a loop */
int main()
{
	GLFWwindow* window;
	int frameBuffW, frameBuffH;
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) 
		return 1;
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "AsteroidGame",NULL ,NULL );
	if (!window) {
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, callback);
	game.start(WIN_WIDTH,WIN_HEIGHT);
	while (!glfwWindowShouldClose(window))
	{
			glfwGetFramebufferSize(window, &frameBuffW, &frameBuffH);
			glViewport(0, 0, frameBuffW, frameBuffH);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			game.update();

			glfwSwapBuffers(window);
			glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}


