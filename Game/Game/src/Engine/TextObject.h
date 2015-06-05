#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "../DebugLog.h"
#include <string>
#include <vector>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class TextObject
{
private:
	int size;
	vec2 pos;
	vector<vec2> vertices;

	void setupText(string str, vec2 screenPos);
public:
	TextObject(string str, int fontSize, vec2 screenPos);
	~TextObject();
	void getBuffer(int &fSize, vector<vec2> &dataBuf);
	void setText(string str);
};

#endif