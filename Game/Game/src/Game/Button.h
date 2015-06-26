#ifndef BUTTON_H
#define BUTTON_H

#include "../DebugLog.h"
#include "../Engine/TextObject.h"
#include "../Engine/BoxObject.h"
#include <string>
#include <vector>
#include <fstream>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Button
{
private:
	BoxObject* myBox;
	TextObject* myText;
public:
	Button(string text, int fontSize, vec2 &windowPos, vec4 &boxColor, int boxBorderSize);
	~Button();
	TextObject*& getTextObject()
	{
		return myText;
	}
	BoxObject*& getBoxObject()
	{
		return myBox;
	}
};

#endif