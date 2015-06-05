#ifndef ENGINE_H
#define ENGINE_H

#include "../DebugLog.h"
#include "AVIstream.h"
#include "TextObject.h"
#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

class Engine
{
private:
	GLuint bgProgram;
	GLuint textProgram;
	string getShader(const char* filePath);
	void buildBgShaderProgram();
	void buildTextShaderProgram();
	void compileErrorPrint(GLuint* shader);
	void linkErrorPrint(GLuint* program);

	GLuint screenQuad;
	GLuint fontSize16;
	bool loadPNG(string filePath, GLuint &texture);
	void RenderText(TextObject* text);
	GLuint textDataBuffer;
public:
	Engine();
	void Render(float dT, AVIstream* bg, vector<TextObject*> text);
};

#endif