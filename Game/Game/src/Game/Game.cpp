#include "Game.h"
#include "../Engine/TextObject.h"
#include <sstream>

#include "../Settings.h"

#include <ctime>

int Game::cursorMessage = -1;
double Game::cursorX = -1.0;
double Game::cursorY = 1.0f;

void Game::cursorCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		cursorMessage = button;
	}
}

Game::Game(GLFWwindow* window)
{
	wnd = window;
	glfwSetMouseButtonCallback(window, cursorCallback);

	engine = new Engine();
}

Game::~Game()
{
	delete currentScene;
	delete engine;
}

int Game::update(float dT)
{
	currentScene->update(cursorX, cursorY);
	if (cursorMessage == GLFW_MOUSE_BUTTON_LEFT)
	{
		printf("Click! Cursor position is (%f, %f)\n", cursorX, cursorY);
		cursorMessage = -1;

		currentScene->sceneClick(cursorX, cursorY);
	}
	if (cursorMessage == GLFW_MOUSE_BUTTON_RIGHT)
	{
		
	}
	engine->Render(dT, currentScene->getBackground(), currentScene->getText(), currentScene->getBoxes());
	return 0;
}

void Game::mainLoop()
{
	currentScene = new Scene("scene.txt");

	clock_t start = clock();
	float deltaTime = 0.0f;
	float clock;
	float lastClock = 0.0f;
	int fpsCount = 0;
	while (!glfwWindowShouldClose(wnd))
	{
		glfwPollEvents();
		clock = float((std::clock() - start) / (double)CLOCKS_PER_SEC);
		deltaTime = clock - lastClock;
		lastClock = clock;

		glfwGetCursorPos(wnd, &cursorX, &cursorY);
		update(deltaTime);
		glfwSwapBuffers(wnd);
	}
}