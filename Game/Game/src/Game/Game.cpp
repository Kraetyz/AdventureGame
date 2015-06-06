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
		glfwGetCursorPos(window, &cursorX, &cursorY);
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
	delete engine;
}

int Game::update(float dT)
{
	if (cursorMessage == GLFW_MOUSE_BUTTON_LEFT)
	{
		printf("Click! Cursor position is (%f, %f)\n", cursorX, cursorY);
		cursorMessage = -1;

		currentScene->sceneClick(0, 0);
	}
	if (cursorMessage == GLFW_MOUSE_BUTTON_RIGHT)
	{
		cursorMessage = -1;
		currentScene->sceneClick(1, 0);
	}
	return 0;
}

void Game::mainLoop()
{
	currentScene = new Scene();

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

		update(deltaTime);
		engine->Render(deltaTime, currentScene->getBackground(), currentScene->getText());
		glfwSwapBuffers(wnd);
	}
}