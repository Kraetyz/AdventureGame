#include "Game.h"
#include "../Engine/TextObject.h"
#include <sstream>

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

Game::Game(GLFWwindow* window, int width, int height)
{
	wnd = window;
	glfwSetMouseButtonCallback(window, cursorCallback);

	engine = new Engine();

	WIDTH = width;
	HEIGHT = height;
}

Game::~Game()
{
	delete engine;
}

int Game::update(float dT)
{
	if (cursorMessage == GLFW_MOUSE_BUTTON_LEFT)
	{
		stringstream ss;
		ss << "Clicked at position (" << cursorX << ", " << cursorY << ")";
		textObjects[3]->setText(ss.str());
		printf("Click! Cursor position is (%f, %f)\n", cursorX, cursorY);
		cursorMessage = -1;
	}
	return 0;
}

void Game::mainLoop()
{
	AVIstream* back = new AVIstream("villagehq.avi");
	TextObject* text = new TextObject("This is a whole bunch of text.\nIt even has a line break!\nDo you like it?", 12, vec2(200, 400));
	TextObject* bigText = new TextObject("Large text!", 18, vec2(300, 200));
	TextObject* fpsCounter = new TextObject("Lol", 16, vec2(20, 20));
	TextObject* latestClick = new TextObject("Lol", 16, vec2(20, 36));
	textObjects.push_back(text);
	textObjects.push_back(bigText);
	textObjects.push_back(fpsCounter);
	textObjects.push_back(latestClick);
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
		stringstream ss;
		ss << "FPS: " << int(1/(deltaTime));
		textObjects[2]->setText(ss.str());
		engine->Render(deltaTime, back, textObjects);
		glfwSwapBuffers(wnd);
	}
	delete back;
	delete text;
	delete bigText;
	delete fpsCounter;
	delete latestClick;
}