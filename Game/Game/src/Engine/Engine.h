#ifndef ENGINE_H
#define ENGINE_H

#include "../DebugLog.h"
#include "AVIstream.h"
#include "TextObject.h"
#include "BoxObject.h"
#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

class Engine
{
private:
	GLuint aviProgram;
	GLuint textProgram;
	GLuint boxProgram;
	string getShader(const char* filePath);
	void buildAVIShaderProgram();
	void buildTextShaderProgram();
	void buildBoxShaderProgram();
	void compileErrorPrint(GLuint* shader);
	void linkErrorPrint(GLuint* program);

	GLuint screenQuad;
	GLuint fontSize16;
	bool loadPNG(string filePath, GLuint &texture);
	void RenderText(TextObject* text);
	void RenderTextBox(BoxObject* box);

	GLuint textDataBuffer;
	GLuint boxBuffer;
public:
	Engine();
	void Render(float dT, AVIstream* bg, vector<TextObject*> text, vector<BoxObject*> boxes);
};

#endif