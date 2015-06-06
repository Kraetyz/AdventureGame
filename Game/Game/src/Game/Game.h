#ifndef GAME_H
#define GAME_H

#include "../DebugLog.h"
#include "../Engine/Engine.h"
#include "../Engine/AVIstream.h"
#include "Scene.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Game
{
private:
	//Mouse callback statics
	static void cursorCallback(GLFWwindow* window, int button, int action, int mods);
	static int cursorMessage;
	static double cursorX;
	static double cursorY;
	//End mouse statics

	GLFWwindow* wnd;
	Engine* engine;

	int update(float dT);

	Scene* currentScene;
public:
	Game(GLFWwindow* window);
	~Game();
	void mainLoop();
};

#endif