#include "Engine.h"
#include <stb_image.h>

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

Engine::Engine()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	buildAVIShaderProgram();
	buildTextShaderProgram();
	buildBoxShaderProgram();


	float screenquad[] =
	{
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0, 0.0f,
		-1.0f, -1.0f, 0.0f
	};
	glGenBuffers(1, &screenQuad);
	glBindBuffer(GL_ARRAY_BUFFER, screenQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screenquad), screenquad, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	loadPNG("font16.png", fontSize16);
	glGenBuffers(1, &textDataBuffer);

	glGenBuffers(1, &boxBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, boxBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screenquad), screenquad, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::buildAVIShaderProgram()
{
	string vShader = "";
	vShader = getShader("shaders/bgVertex.txt");
	string fShader = "";
	fShader = getShader("shaders/bgFragment.txt");

	const char* vertex_shader = vShader.c_str();
	const char* fragment_shader = fShader.c_str();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);
	compileErrorPrint(&vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);
	compileErrorPrint(&fs);

	aviProgram = glCreateProgram();
	glAttachShader(aviProgram, vs);
	glAttachShader(aviProgram, fs);
	glLinkProgram(aviProgram);
}

void Engine::buildTextShaderProgram()
{
	string vShader = "";
	vShader = getShader("shaders/textVertex.txt");
	string fShader = "";
	fShader = getShader("shaders/textFragment.txt");

	const char* vertex_shader = vShader.c_str();
	const char* fragment_shader = fShader.c_str();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);
	compileErrorPrint(&vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);
	compileErrorPrint(&fs);

	textProgram = glCreateProgram();
	glAttachShader(textProgram, vs);
	glAttachShader(textProgram, fs);
	glLinkProgram(textProgram);
}

void Engine::buildBoxShaderProgram()
{
	string vShader = "";
	vShader = getShader("shaders/boxVertex.txt");
	string fShader = "";
	fShader = getShader("shaders/boxFragment.txt");

	const char* vertex_shader = vShader.c_str();
	const char* fragment_shader = fShader.c_str();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);
	compileErrorPrint(&vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);
	compileErrorPrint(&fs);

	boxProgram = glCreateProgram();
	glAttachShader(boxProgram, vs);
	glAttachShader(boxProgram, fs);
	glLinkProgram(boxProgram);
	linkErrorPrint(&boxProgram);
}

#include <vector>
void Engine::compileErrorPrint(GLuint* shader)
{
	GLint success;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv((*shader), GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog((*shader), maxLength, &maxLength, &errorLog[0]);

		std::fstream myfile;
		myfile.open("errorCheck.txt", std::fstream::out);
		for (int i = 0; i < maxLength; i++)
		{
			myfile << errorLog[i];
		}
		myfile.close();

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(*shader); // Don't leak the shader.
		throw;
	}
}
void Engine::linkErrorPrint(GLuint* shaderProgram)
{
	GLint success;
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(*shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(*shaderProgram, maxLength, &maxLength, &errorLog[0]);

		std::fstream myfile;
		myfile.open("errorLinkCheck.txt", std::fstream::out);
		for (int i = 0; i < maxLength; i++)
		{
			myfile << errorLog[i];
		}
		myfile.close();

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteProgram(*shaderProgram); // Don't leak the shader.
		throw;
	}
}

string Engine::getShader(const char* filePath)
{
	ifstream myReadFile;
	myReadFile.open(filePath);
	std::string content = "";
	std::string line;

	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			std::getline(myReadFile, line);
			content.append(line + "\n");
		}
	}
	myReadFile.close();
	return content;
}

void Engine::Render(float dT, AVIstream* bg, vector<TextObject*> text, vector<BoxObject*> boxes)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(aviProgram);
	bg->GrabAVIFrame(dT);
	glBindTexture(GL_TEXTURE_2D, bg->getTex());
	glBindBuffer(GL_ARRAY_BUFFER, screenQuad);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	for (int c = 0; c < boxes.size(); c++)
		RenderTextBox(boxes[c]);

	for (int c = 0; c < text.size(); c++)
		RenderText(text[c]);
}

void Engine::RenderText(TextObject* text)
{
	glUseProgram(textProgram);
	int fontSize=0;
	vector<vec2> textBuffer;
	text->getBuffer(fontSize, textBuffer);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, textDataBuffer);
	glBufferData(GL_ARRAY_BUFFER, textBuffer.size() * sizeof(vec2), &textBuffer[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindTexture(GL_TEXTURE_2D, fontSize16);

	glDrawArrays(GL_TRIANGLES, 0, textBuffer.size());
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}

void Engine::RenderTextBox(BoxObject* box)
{
	vec4 borders, color;
	float* quad = new float[12];
	box->getBoxAttributes(color, borders, quad);

	glUseProgram(boxProgram);
	GLuint loc = glGetUniformLocation(boxProgram, "boxColor");
	glUniform4fv(loc, 1, &color[0]);
	loc = glGetUniformLocation(boxProgram, "borders");
	glUniform4fv(loc, 1, &borders[0]);

	glBindBuffer(GL_ARRAY_BUFFER, boxBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*12, quad, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[]quad;
}

bool Engine::loadPNG(string filePath, GLuint &texture)
{
	int x, y, compress;
	GLubyte* image = stbi_load((string("Media/PNG/").append(filePath)).c_str(), &x, &y, &compress, 0); //change the last 0 to 1

	if (image == nullptr)
		throw(std::string("Failed to load texture"));

	glGenTextures(1, &texture);

	glActiveTexture(GL_TEXTURE0);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}